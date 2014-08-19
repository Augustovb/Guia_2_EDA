
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Robot.h"


/*
 *          Source code de funciones de la Guia 2
 *          Ejercicios 4-11
 *
 */




double getDistanceBetweenPoints (Point p1 , Point p2){
	// la distancia es la raiz de (x1-x2) cuadrado + (y1-y2) al cuadrado

	double Distance;

	Distance= sqrt (pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));

	return Distance;

}



Point translatePoint (Point p, double distance, double angle){
    
	Point Destiny;		//Me imagino el punto p recibido como si tuviese capacidad de trasladarse. Luego de 
						//moverse una distancia "distance" a un angulo "angle" habra llegado a Destiny.

	//El problema es que el seno y el coseno, no estan exactamente como yo deseo, ya que mi 0 es el norte. La solucion
	//es ponerle un angulo de fase al coseno y al seno

	Destiny.x=p.x+(sin(angle))*distance;	//es como un triangulo donde conozco el angulo y la distancia
	Destiny.y=p.y-(cos(angle))*distance;	//teniendo uno de los vertices de la hipotenusa y buscando el otro

	return Destiny;
}



double getAngleBetweenPoints (Point p1, Point p2){
	double Angle;
	double Pendiente;		//me imaginare como si hubiese una recta uniendo estos dos puntos
							//obtendre la pendiente de esta recta y luego tendre el angulo entre los dos

	Pendiente= (p1.y-p2.y)/(p1.x-p2.x);


	Angle= atan (Pendiente);		//el angulo es el arcotangente de la pendiente

	//Quiero que los angulos tengan como 0 el norte cuando el eje de coordenadas lo centro en el punto p1:
	if(p2.x>p1.x && p2.y<p1.y){		//si no le sumo el angulo me devuelve angulos del -pi/2 a 0

		Angle+=PI/2;
	} else if (p2.x>=p1.x && p2.y>=p1.y){ //si no... 0 a pi/2

		Angle+=PI/2;
	} else if(p2.x <p1.x && p2.y > p1.y){ //si no... de -pi/2 a 0

		Angle+=(3.0/2.0)*(PI);
	} else if(p2.x <p1.x && p2.y < p1.y){ // si no .. de 0 a pi/2

		Angle+=(3.0/2.0)*(PI);
	} else if(p2.x == p1.x){
		Angle=0.0;
	} else {

		printf("Error en la interpretacion correcta del angulo.\n");
		
	}



	return Angle;
}



bool isPointEqual (Point p1, Point p2){
	double resultado;

	resultado=getDistanceBetweenPoints(p1,p2);

	if(resultado< PRECISION){
	return true;
	} else {
		return false;
	}

}



double getRectArea (Rect r){
	double Area;


	Area=(getModuloDe(r.bottomP1.x-r.bottomP2.x))*(getModuloDe(r.upperP1.y-r.bottomP2.y));	//Base*Altura

	return Area;
}



double getModuloDe(double number){
	if (number>0){
		return number;
	} else{

		return -number;
	}
}

bool isPointInRect(Point p, Rect r)
{

    if ((p.x >= r.bottomP1.x) && (p.x <= r.upperP2.x)) {
        if ((p.y <= r.bottomP1.y) && (p.y >= r.upperP2.y))
            return true;
    }
    else {
        return false;
    }
        

}