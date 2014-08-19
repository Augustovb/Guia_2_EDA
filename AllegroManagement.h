/* 
 * File:   AllegroManagement.h
 * Author: augustovb
 *
 * Created on August 19, 2014, 12:52 AM
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#ifndef ALLEGROMANAGEMENT__H
#define	ALLEGROMANAGEMENT__H

/*****************************************************
 * 
 *             Funciones especificas de allegro      *
 *
 *****************************************************/


int initializeAllegro(void);                        //inicializa allegro
void closeAllegro(void);                            //lo cierra


ALLEGRO_DISPLAY* getDisplay(int ancho, int alto);   //devuelve el display con el alto y ancho pedido



ALLEGRO_TIMER* getTimer (float periodo);            //un timer que genera eventos por cada periodo



ALLEGRO_FONT* crearFuente (int tamano);             //crea una fuente del ttf en la carpeta destino con el tamaño pedido












#endif	/* ALLEGROMANAGEMENT_H */

