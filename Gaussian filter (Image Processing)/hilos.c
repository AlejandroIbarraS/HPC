#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include "imagen.h"


extern pthread_mutex_t bloqueo;
int kernelGaussiano[DIMASK*DIMASK] = {
	1,  4,  7,  4, 1,
	4, 20, 33, 20, 4,
	7, 33, 54, 33, 7,
	4, 20, 33, 20, 4,
	1,  4,  7,  4, 1 
};
extern unsigned char *imagenGG, *imagenFG;
extern uint32_t width, height;

//Hilos bloque
void * funHilo( void * arg )
{
	int nucleo = *(int *)arg;
	int eleBloque = (height-DIMASK+1) / NUM_HILOS;	//tamaño de bloque
	int iniBloque = nucleo * eleBloque;
	int finBloque = iniBloque + eleBloque;

	printf("Hilo %d en ejecucion \n", nucleo);

	register int x, y, xm, ym;
	int indicem, indicei, conv;
 
	for( y=iniBloque; y<finBloque ; y++ )//Este ciclo es el que se paraleliza
		for( x=0; x<=width-DIMASK; x++ ){
			indicem=0;
			conv=0;
			for( ym=0; ym<DIMASK; ym++ )
				for( xm=0; xm<DIMASK; xm++ ){
					indicei = (y+ym)*width + (x+xm);
					conv+=imagenGG[indicei]*kernelGaussiano[indicem++];
				}
			conv=conv/FACTOR;
			indicei = (y+1)*width + (x+1);
			//pthread_mutex_lock(&bloqueo);
			imagenFG[indicei]=conv;
			//pthread_mutex_unlock(&bloqueo);
		}
	pthread_exit( arg );
}


