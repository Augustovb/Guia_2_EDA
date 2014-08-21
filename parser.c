
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "Robot.h"


int parseCmdLine(int argc, char *argv[], pCallback callback, void *userData){
    
    
    int i;                 //variable del loop
    unsigned int estado=0;          //chequeo de estados
    
    for(i=1; i<argc; ++i){          //comienza en uno ya qe argv[0] == nombre del ejecutable, en nuestro caso el main_guia1
        
        if((* argv[i])=='-'){         //estoy por leer una opcion
            
            //debo chequear dos cosas: que no sea vacia la "opcion" es decir un '-' por si mismo
            //y que el proximo argumento, exista y no sea otra opcion
            if(((*argv[i])+1)=='\0'){
              
                return ERROR;
            }
            
            if((i+1)==argc){
                            
            return ERROR;       //se paso como ultimo elemento una opcion sin valor
            }
            
            
            
            //finalmente si todo esta bien, llamo al callback
            
            estado=callback(argv[i]+1,argv[i+1], userData);  //debo chequear si hubo errores
            
            if(estado==ERROR){
                return ERROR;
            }
			
            ++i;
            
        } else {                    //estoy por leer un parametro
            
            estado= callback(NULL, argv[i], userData);  //el key es null, es un parametro
            
            if(estado==ERROR){
                return ERROR;
            } 
            
        }
        
		
    }
    
    return 0; 
}

