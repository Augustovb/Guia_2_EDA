#include <allegro5/allegro.h>
#include "AllegroManagement.h"
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


#ifndef SIMULATOR_H
#define SIMULATOR_H

/*Constantes*/

#define DESPLAZAMIENTO 1
#define TAMANOBALDOSA 5
#define TAMANOBALDOSAALLEGRO 25

/*FUNCIONES DE SIMULACION*/

/*Funcion principal de simulacion en tiempo real*/
/*Recibe una estructura con los datos necesarios para la simulacion: punteros a robots y piso y numero de robots*/
/*Devuelve la cantidad de ticks que le llevo a los robots limpiar*/
float realSimulator (simulacionType simulacion);

/*Funcion que mueve los robots en la direccion a la cual apuntan*/
/*Si llega al borde hace variar su direccion aleatoriamente*/
void moverRobots (simulacionType simulacion);

/*Limpia la baldosa donde se encuentra el/los robot/s*/
void limpiarBaldosa (simulacionType simulacion);

/*Determina si se limpio todo el piso*/
int checkFloor (simulacionType simulacion);


/* Igual que realsimulator, simplemente se le agregaron funciones graficadoras*/
float allegroSimulator (simulacionType simulacion);
void limpiarBaldosaAllegro (simulacionType simulacion);
void moverRobotsAllegro (simulacionType simulacion);
void grafRobot (robotType robot,ALLEGRO_BITMAP* R2D2);
void graficarPiso (simulacionType simulacion, ALLEGRO_BITMAP* baldosaSucia, ALLEGRO_BITMAP* baldosaLimpia);
void graficarRobots (simulacionType simulacion,ALLEGRO_BITMAP* R2D2);


#endif