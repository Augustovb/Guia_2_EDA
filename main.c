#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Robot.h"
#include "parser.h"
#include <allegro5/allegro.h>
#include "AllegroManagement.h"
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>





int main (int argc , char* argv[]){
    
	int estado=0;
	userData data={5,5,1,VISUAL};  /*Estructura que contendra la informacion que se pareseara*/
	void* pdata;
	simulacionType simulacion;	//creo una estructura de la simulacion

	pdata=&data;
        
	//estado= parseCmdLine (argc,argv, parseCallback, pdata);
        
        //estado=checkParameters(data);
        
	//if(estado==ERROR){
	//	printf("Hubo un problema con la toma de parametros.\n");
	//	return ERROR;
	//}

        
        
        
      
        
         if (data.modo == VISUAL){
        
             estado=initializeAllegro();
             if(estado==ERROR){
		printf("Hubo un problema con la inicializacion de Allegro\n");
		return ERROR;
            }
             pisoType piso;
             robotType *robots;               
                    
             piso = crearPiso (data.largo, data.ancho);
             robots = crearRobots (data.robots, piso);
                                                 
             simulacion.piso = &piso;
             simulacion.robots = robots;
             simulacion.robotCount = data.robots;
             
             allegroSimulator (simulacion);     //no lo devuelvo a ningun valor ya que no me aporta informacion aqui el promedio
             
             
             
            
             closeAllegro();
        }
        
        else {
            
            unsigned int i=0;
            float promedio = 0;
            float promedion1 = 0;
            
            do {
                for (i=0; i<1000; i++)
                {
                
                    //Crear piso, robots, simulo, destruyo todo
                    pisoType piso;
                    robotType *robots;               
                    
                    piso = crearPiso (data.largo, data.ancho);
                    robots = crearRobots (data.robots, piso);
                                                 
                    simulacion.piso = &piso;
                    simulacion.robots = robots;
                    simulacion.robotCount = data.robots;
                    
                    promedio = realSimulator (simulacion);
                                 
                    //free (piso.baldosas);
                    //free (robots);
                    
                    return 0;
                } 
                
            } while ((promedion1 - promedio) < 0.1);
        }

        
	return 0;
}


int parseCallback(char *key, char *value, void *dataUsuario){
	
	userData* datos;
	unsigned int prueba=0;
	datos=(userData*) dataUsuario;          //ya tengo un puntero a la data del usuario recibida
	
	if(key==NULL){
        return ERROR;   // no me interesan los parametros, no deberian haberse mandado ya que para este problema, no me serviran
    }
   
	if(strcmp("h",key)==0){		//en parser.h se encuentran los rangos de cada elemento
		prueba=atoi(value);
		if(prueba==0 ||prueba>100){
                        printf ("Valor de h fuera de rango.\n");
			return ERROR;
		}
		datos->largo=prueba;
		return 0;
	} else if(strcmp("w",key)==0){
		prueba=atoi(value);
		if(prueba==0 ||prueba>70){
                        printf ("Valor de w fuera de rango.\n");
			return ERROR;
		}
		datos->ancho=prueba;
		return 0;
	} else if(strcmp("n",key)==0){
		prueba=atoi(value);
		if(prueba==0 ||prueba>60000){
                        printf ("La cantidad de Robots no puede ser nula ni negativa ni mayor a 60000.\n");
			return ERROR;
		}
		datos->robots=prueba;
		return 0;
	} else if (strcmp("t",key)==0){
		prueba=atoi(value);
		if(prueba==0){
                        printf ("El modo 0 no existe. Intente con 1 o 2.\n");
			return ERROR;
		} else if(prueba == 1){
			datos->modo=VISUAL;
			return 0;
		} else if (prueba == 2){
			datos->modo=MILSIMS;
			return 0;
		} else {
                        printf ("El modo introducido es inexistente. Intente con 1 o 2.\n");
			return ERROR;
		}

	} else {
		return ERROR;
	}


	return ERROR;
}


int checkParameters (userData data){
    
    if(data.ancho==0){
        return ERROR;
        
    } else if(data.largo==0){
        return ERROR;
        
    } else if(data.modo==0){
        return ERROR;
        
    } else if(data.robots==0){
        return ERROR;
        
    } else {
        return 0;   
    } 
}