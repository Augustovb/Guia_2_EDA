
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Robot.h"
#include "parser.h"


pisoType crearPiso(unsigned int largo, unsigned int ancho){

	pisoType piso;

	unsigned int i; //para el for

	piso.largo=largo;
	piso.ancho=ancho;

	piso.baldosas=(int*) malloc(largo*ancho*sizeof(int));

	if(piso.baldosas == NULL){			//hubo un problema en la alocacion de la memoria
		printf("No hubo memoria suficiente apara alocar");
		free(piso.baldosas);
                piso.baldosas=NULL;
		return piso;
	}

	for(i=0; i<ancho*largo ; ++i){

		piso.baldosas[i]=SUCIO;
	}
	
	return piso;

}


robotType *crearRobots (unsigned int numero, pisoType piso)
{

    robotType *robots;
    unsigned int i=0;
    
    robots = (robotType *) malloc(numero*sizeof(robotType));
    
    if(robots == NULL){			//hubo un problema en la alocacion de la memoria
		printf("No hubo memoria suficiente apara alocar");
		free(robots);
		return NULL;
	}

    for(i=0; i<numero ; ++i){

        robots[i].angle = randomize (0, 2*PI);
        robots[i].posicion.x = randomize (0, piso.ancho);
        robots[i].posicion.y = randomize (0, piso.largo);
        
    }
    
    return (robots);
    
}


/*VER DONDE PONER ESTA FUNCION DESPUES*/
float randomize (float minval, float maxval)
{
        maxval = maxval * 1000;
	int randomnumber=0;
	static int seed=0;

	if (seed == 0)
		{
		srand (time(NULL));	/*Seed*/ /*Only implants when function is called for the first time*/
		seed++;
		}	

	randomnumber = ( (rand() % ((int)maxval-(int)minval)) + (int)minval);	/*Randomizes according to minval and maxval*/

	return ((float)randomnumber/100);

}