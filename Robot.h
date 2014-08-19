#include <stdio.h>
#include <stdlib.h>

#ifndef ROBOT__H
#define ROBOT__H
/************************
 *		BOOL CREATION	*
 ************************/
#define bool int
#define true 1
#define false 0


/************************
 *		CONSTANTES		*
 ************************/

#define PI 3.141592653589 // solo por precision

#define PRECISION 0.00001


#define ERROR -1
#define SUCIO	0
#define LIMPIO	1

#define VISUAL		10
#define	MILSIMS		20

/************************
 *		DEFINICIONES	*
 ************************/

typedef struct {
	double x;				//un punto tiene una coordenada x y una coordenada y
	double y;
} Point;


typedef struct{
	Point upperP1, upperP2, bottomP1,bottomP2;		//se supone que upper p1 y p2 deben tener igual valor de y, al igual que los bottom

} Rect;

//A partir de ahora seran propias del robot las definiciones

typedef struct {
	Point posicion;

	double angle;			/* De cada robot necesito informar la posicion y el angulo hacia el cual apunta.  */

} robotType;

typedef struct {
	int * baldosas;		//se creara con Malloc( ancho * largo * sizeof(int))

	unsigned int ancho;
	unsigned int largo;

} pisoType;

typedef struct {
	robotType * robots;
	unsigned int robotCount;

	pisoType * piso;

	unsigned int tickCount;			//cantidad de veces que se detecto un tick			Lo realizaremos con los timers de Allegro
	unsigned int ticksPerSecond;    //cantidad de veces por segundo que se realizaran


}simulacionType;


/************************
 *		FUNCIONES		*
 ************************/
/* ACLARACION */
/* Angulos se toman como 0 en el norte */


/* Toma dos puntos y devuelve el angulo que hay entre ellos*/
double getAngleBetweenPoints (Point p1, Point p2);

/* Funcion que recibe dos estructuras punto y obtiene la distancia euclidiana entre ellos*/
double getDistanceBetweenPoints (Point p1 , Point p2);

/* Traslada un punto de una distancia hacia un angulo tomado igual que la funcion get angle*/
Point translatePoint (Point p, double distance, double angle);


/*Chequea segun una PRECISION, si dos puntos son el mismo*/
bool isPointEqual (Point p1, Point p2);


/* Devuelve el area de un rectangulo*/
double getRectArea (Rect r);


/*Devuelve el modulo de un numero entregado*/
double getModuloDe(double number);

/*Funcion que analiza si un punto pertenece o no a un rectangulo*/
bool isPointInRect (Point p, Rect r);



/*Crea un piso segun lo recibido para el robot*/
pisoType crearPiso (unsigned int largo, unsigned int ancho);

/*Crea los robots pedidos para la simulacion*/
robotType *crearRobots (unsigned int numero, pisoType);

/*Funcion que tira numeros aleatorios entre minval y maxval*/
float randomize (float minval, float maxval);

#endif
