/*In honor of Goat Simulator, this is our first simulator ever*/

#include <stdio.h>
#include <stdlib.h>
#include "Robot.h"
#include "parser.h"
#include <math.h>
#include "Simulator.h"
#include <allegro5/allegro.h>
#include "AllegroManagement.h"
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


float realSimulator (simulacionType simulacion)
{

    int estado = SUCIO;
    float tick = 0;
    
                                          
    while (estado != LIMPIO) {             //while el piso este todo sucio
    
        moverRobots (simulacion);
        limpiarBaldosa (simulacion);
    
        if(checkFloor(simulacion))
            estado = LIMPIO;
        
        tick++;
    
    }
    
    return tick;
}



void moverRobots (simulacionType simulacion)
{

    unsigned int i=0;
    
    for (i=0 ; i<simulacion.robotCount; i++)    /*Muevo los robots cierto desplazamiento, en el mismo angulo*/
    {
    
        simulacion.robots[i].posicion = translatePoint (simulacion.robots[i].posicion, DESPLAZAMIENTO, simulacion.robots[i].angle);
    
        if (simulacion.robots[i].posicion.x > simulacion.piso->ancho*TAMANOBALDOSA-PRECISION) {
            simulacion.robots[i].posicion.x = simulacion.piso->ancho*TAMANOBALDOSA-PRECISION;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }                                                               /*Si se paso del borde, lo dejo justo en el borde*/
        
        if (simulacion.robots[i].posicion.x < 0) {                       /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.x = 0;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
        
        if (simulacion.robots[i].posicion.y > simulacion.piso->largo*TAMANOBALDOSA-PRECISION) {   /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.y = simulacion.piso->largo*TAMANOBALDOSA-PRECISION;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
        if (simulacion.robots[i].posicion.y < 0) {                      /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.y = 0;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
    }

}

void limpiarBaldosa (simulacionType simulacion)
{

    unsigned int i=0;
    float baldosax;
    float baldosay;
    
    int offset = simulacion.piso->ancho;
    
    for (i=0 ; i<simulacion.robotCount; i++)    /*Muevo los robots cierto desplazamiento, en el mismo angulo*/
    {
   
        baldosax = simulacion.robots[i].posicion.x/TAMANOBALDOSA;
        baldosay = simulacion.robots[i].posicion.y/TAMANOBALDOSA;
        
        simulacion.piso->baldosas[(int)baldosay*(int)offset + (int)baldosax] = LIMPIO;  /*Se pasa la escoba, se limpio el piso*/
             
    
    }

}

int checkFloor (simulacionType simulacion)
{

    unsigned int i=0;
    
    for (i=0; i<(simulacion.piso->ancho)*(simulacion.piso->largo); i++)
    {
    
        if (simulacion.piso->baldosas[i] == SUCIO)  /*Recorre las baldosas, revisando su estado de suciedad*/
            return false;
    
    }
    
    return true;

}





float allegroSimulator (simulacionType simulacion){
    int estado = SUCIO;
    float tick = 0;
    //creaciones de bitmaps
    ALLEGRO_BITMAP* clean=NULL;
    ALLEGRO_BITMAP* dirty=NULL;
    ALLEGRO_BITMAP* robot=NULL;
    ALLEGRO_BITMAP* fondo=NULL;
    ALLEGRO_DISPLAY* display=NULL;
    display=al_create_display(TAMANOBALDOSAALLEGRO*simulacion.piso->ancho,TAMANOBALDOSAALLEGRO*simulacion.piso->largo);
    clean=al_create_bitmap(TAMANOBALDOSAALLEGRO-1,TAMANOBALDOSAALLEGRO-1);
    dirty=al_create_bitmap(TAMANOBALDOSAALLEGRO-1,TAMANOBALDOSAALLEGRO-1);
    
    if(clean ==NULL || dirty == NULL || display== NULL ){
        al_destroy_bitmap(dirty);
        al_destroy_bitmap(clean);
        al_destroy_display(display);
        
        fprintf(stderr,"Error al crer bitmaps\n");
        exit -1;
    }
    robot=al_load_bitmap("R2D2.png");
    if(robot==NULL){
        printf("No se pudo cargar la imagen \n");
        exit-1;
    }
    al_set_target_bitmap(clean);
    al_clear_to_color(al_map_rgb(250,250,250));
    al_set_target_bitmap(dirty);
    al_clear_to_color(al_map_rgb(180,180,180));
    
    
    
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0,0,0));
    graficarPiso(simulacion,dirty,clean);
    al_flip_display();
    graficarRobots(simulacion,robot);
    al_flip_display();
    
    //creaciones de comienzo de entorno grafico
                                          
    while (estado != LIMPIO) {             //while el piso este todo sucio
    
        moverRobotsAllegro (simulacion);
        limpiarBaldosaAllegro (simulacion);
        
        graficarPiso(simulacion,dirty,clean);
        graficarRobots(simulacion,robot);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    
        if(checkFloor(simulacion))
            estado = LIMPIO;
        
        
        tick++;
    
    }
    
    al_destroy_display(display);
    al_destroy_bitmap(clean);
    al_destroy_bitmap(dirty);
    al_destroy_bitmap(robot);
    
    
    return tick;
}


void graficarPiso (simulacionType simulacion, ALLEGRO_BITMAP* baldosaSucia, ALLEGRO_BITMAP* baldosaLimpia){
    // el tamaño del display es TAMANOBALDOSAALLEGRO*simulacion.piso->ancho,TAMANOBALDOSAALLEGRO*simulacion.piso->largo
    unsigned int i,j;   //para el for
    unsigned int ancho,largo;
    
    ancho=simulacion.piso->ancho;
    largo=simulacion.piso->largo;
    
    
    
    for(i=0; i<simulacion.piso->ancho ; ++i){
        for (j=0; j< simulacion.piso->ancho ; ++j){
            
            if(*((simulacion.piso->baldosas)+i*(simulacion.piso->ancho)+j)==LIMPIO){        //si tal baldosa esta limpia, grafico en el lugar de la baldosa, el bitmap
                
                al_draw_bitmap(baldosaLimpia,i*TAMANOBALDOSAALLEGRO,j*TAMANOBALDOSAALLEGRO,0);
                
            } else {
              
                al_draw_bitmap(baldosaSucia,i*TAMANOBALDOSAALLEGRO,j*TAMANOBALDOSAALLEGRO,0);
            }
             
        }
    }
    
    
}


void graficarRobots (simulacionType simulacion,ALLEGRO_BITMAP* R2D2){
    unsigned int n;     //para los robots
    
    for(n=0; n<simulacion.robotCount ; ++n){
        grafRobot(simulacion.robots[n], R2D2);
    }
    
    
}
void grafRobot (robotType robot, ALLEGRO_BITMAP* R2D2){
    
    //void al_draw_rotated_bitmap(ALLEGRO_BITMAP *bitmap,float cx, float cy, float dx, float dy, float angle, int flags)
    al_draw_bitmap(R2D2, robot.posicion.y-5, robot.posicion.x-5,0);
    
}


void moverRobotsAllegro (simulacionType simulacion)
{

    unsigned int i=0;
    
    for (i=0 ; i<simulacion.robotCount; i++)    /*Muevo los robots cierto desplazamiento, en el mismo angulo*/
    {
    
        simulacion.robots[i].posicion = translatePoint (simulacion.robots[i].posicion, DESPLAZAMIENTO, simulacion.robots[i].angle);
    
        if (simulacion.robots[i].posicion.x > simulacion.piso->ancho*TAMANOBALDOSAALLEGRO-PRECISION) {
            simulacion.robots[i].posicion.x = simulacion.piso->ancho*TAMANOBALDOSAALLEGRO-PRECISION;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }                                                               /*Si se paso del borde, lo dejo justo en el borde*/
        
        if (simulacion.robots[i].posicion.x < 0) {                       /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.x = 0;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
        
        if (simulacion.robots[i].posicion.y > simulacion.piso->largo*TAMANOBALDOSAALLEGRO-PRECISION) {   /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.y = simulacion.piso->largo*TAMANOBALDOSAALLEGRO-PRECISION;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
        if (simulacion.robots[i].posicion.y < 0) {                      /*Si se paso del borde, lo dejo justo en el borde*/
            simulacion.robots[i].posicion.y = 0;
            simulacion.robots[i].angle = randomize (0, 2*PI);
        }
    }

}

void limpiarBaldosaAllegro (simulacionType simulacion)
{

    unsigned int i=0;
    float baldosax;
    float baldosay;
    
    int offset = simulacion.piso->ancho;
    
    for (i=0 ; i<simulacion.robotCount; i++)    /*Muevo los robots cierto desplazamiento, en el mismo angulo*/
    {
   
        baldosax = simulacion.robots[i].posicion.x/TAMANOBALDOSAALLEGRO;
        baldosay = simulacion.robots[i].posicion.y/TAMANOBALDOSAALLEGRO;
        
        simulacion.piso->baldosas[(int)baldosay*(int)offset + (int)baldosax] = LIMPIO;  /*Se pasa la escoba, se limpio el piso*/
             
    
    }

}