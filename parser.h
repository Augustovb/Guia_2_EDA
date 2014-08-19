#include <stdio.h>
#include <stdlib.h>


#ifndef FRACTALLIB__H
#define FRACTALLIB__H

typedef struct {
	unsigned int ancho;

	unsigned int largo;

	unsigned int robots;

	unsigned int modo;

}userData;


/********************************************
*		Recibimiento de informacion			*
*********************************************/



/*		Se recibira por linea de comandos lo siguiente:
*
*		largo -h debera ser <100
*		ancho -w debera ser <70		
*
*		cantidad de robots para la simulacion -n
*
*		-t tipo de simulacion	1= simulacion visual
*								2= las 1000 simulaciones
*
*/


typedef int (*pCallback) (char * key, char* value, void *userData);


int parseCmdLine(int argc, char *argv[], pCallback callback, void *userData); 


int parseCallback(char *key, char *value, void *dataUsuario); 

/* Funcion extra que se encarga del chequeo de que se hayan ingresado todos los parametros*/

int checkParameters (userData data);


#endif