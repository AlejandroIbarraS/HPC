#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "imagen.h"
#include "hilos.h"
#include "defs.h"

pthread_mutex_t bloqueo;
unsigned char *imagenGG, *imagenFG;
extern uint32_t width, height;



void filtroPB(unsigned char *imagenG, unsigned char *imagenF, uint32_t width, uint32_t height){
	//Con hilos
	register int nh;
	imagenGG = imagenG;
	imagenFG = imagenF; 
	pthread_mutex_init( &bloqueo, NULL);
	pthread_t tids[NUM_HILOS];
	int *hilo;
	int nhs[NUM_HILOS];
	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}
	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo);
		printf("El hilo %d termino \n", *hilo);	
	}
	pthread_mutex_destroy(&bloqueo);
	//Fin hilos




}



void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height ){
	register int indiceGray;
	int pixel;
	for( indiceGray=0; indiceGray<(width*height); indiceGray++){
		pixel = imagenGray[indiceGray] +70;
		imagenGray[indiceGray]= (pixel > 255)? 255 : (unsigned char)pixel;
	}
}

unsigned char * reservarMemoria( uint32_t width, uint32_t height){
	unsigned char * imagen;
	imagen=(unsigned char *)malloc(width*height*sizeof(unsigned char));
	if( imagen == NULL ){
		perror("Error al asignar memoria a la imagen");
		exit(EXIT_FAILURE);
	}
	

	return imagen;
}




void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height){
	unsigned char nivelGris;
	int indiceRGB, indiceGray;
	//for( y=0 ; y<height ; y++)
		for( indiceGray=0,indiceRGB=0; indiceGray<(width*height); indiceGray++, indiceRGB+=3){
			//nivelGris = (imagenRGB[indiceRGB] + imagenRGB[indiceRGB+1] + imagenRGB[indiceRGB+2])/3;
			nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2])/100;
			imagenGray[indiceGray] = nivelGris;
		}
	
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height){
	int indiceRGB, indiceGray;
	//for( y=0 ; y<height ; y++)
		for( indiceGray=0,indiceRGB=0; indiceGray<(width*height); indiceGray++, indiceRGB+=3){
			imagenRGB[indiceRGB] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
		}
}


/*
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height){
	register int x, y;
	unsigned char nivelGris;
	int indiceRGB, indiceGray;
	for( y=0 ; y<height ; y++)
		for( x=0; x<width; x++){
			indiceGray = y * width + x;
			indiceRGB = indiceGray * 3;
			//nivelGris = (imagenRGB[indiceRGB] + imagenRGB[indiceRGB+1] + imagenRGB[indiceRGB+2])/3;
			nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2])/100;
			imagenGray[indiceGray] = nivelGris;
		}
	
}
*/


/*
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height){
	register int x, y;
	int indiceRGB, indiceGray;
	for( y=0 ; y<height ; y++)
		for( x=0; x<width; x++){
			indiceGray = y * width + x;
			indiceRGB = indiceGray * 3;
			imagenRGB[indiceRGB] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
			imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
		}
}*/


