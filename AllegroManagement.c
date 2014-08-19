#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Robot.h"
#include "parser.h"
#include "AllegroManagement.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>







ALLEGRO_DISPLAY* getDisplay(int ancho, int alto){
    
    ALLEGRO_DISPLAY* display=NULL;
    
    display=al_create_display(ancho,alto);
    if(display==NULL){
        fprintf(stderr,"No se pudo inicializar el display\n"); 
        al_destroy_display(display);
        exit -1;
    }    //inicializar display
    
    return display;
}


ALLEGRO_TIMER* getTimer (float periodo){
    ALLEGRO_TIMER* timer=NULL;
    
    timer=al_create_timer(periodo);
    if(timer==NULL){
        fprintf(stderr,"No se pudo inicializar el timer\n");
        al_destroy_timer(timer);
        exit -1;
    }
    
    return timer;
    
}


ALLEGRO_FONT* crearFuente (int tamano){
    ALLEGRO_FONT* fuente=NULL;
    
    fuente=al_load_ttf_font("PTS55F.ttf",tamano,0);      //cargo la fuente predeterminada con el tamano pedido
    
    
    if (fuente==NULL){
        fprintf(stderr,"No se pudo cargar la imagen, el programa finalizara.\n");
        al_destroy_font(fuente);
        exit -1;
    }
    
    return fuente;
    
}



int initializeAllegro(void){
    if(!al_init()){
        fprintf(stderr,"No se pudo inicializar Allegro\n");
        return ERROR;
    }
    if(!al_install_mouse()){
        fprintf(stderr,"No se pudo inicializar el mouse.\n");
        al_uninstall_system();
        return ERROR;
    }
    if(!al_init_primitives_addon()){
        fprintf(stderr,"No se pudo inicializar el mouse.\n");
        al_uninstall_system();
        al_uninstall_mouse();
        return ERROR;
        
    }
    al_init_font_addon();       //esta funcion en su declaracion dice que devuelve VOID, por eso no puedo hacer el chequeo
    
    if(!al_init_ttf_addon()){
        fprintf(stderr,"No se pudo inicializar el mouse.\n");
        al_uninstall_system();
        al_uninstall_mouse();
        al_shutdown_primitives_addon;
        al_shutdown_font_addon();
        return ERROR;
        
    }
    if(!al_init_image_addon()){
        fprintf(stderr,"No se inicializo el addon de imagenes\n");
        fprintf(stderr,"No se pudo inicializar el mouse.\n");
        al_uninstall_system();
        al_uninstall_mouse();
        al_shutdown_primitives_addon;
        al_shutdown_font_addon();
        al_shutdown_ttf_addon();
        return ERROR;
    } 
    
    return 0;
}








void closeAllegro(void){
    al_uninstall_system(); 
    
    al_uninstall_mouse();
    
    al_shutdown_primitives_addon;
    
    al_shutdown_font_addon(); 
    
    al_shutdown_ttf_addon();
    
    al_shutdown_image_addon();
    
    al_uninstall_system(); 
    
}