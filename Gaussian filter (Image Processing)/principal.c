#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagen.h"
#include "defs.h"
#include "procesamiento.h"


unsigned char *imagenGray, *imagenFiltrada;
uint32_t width, height;

int main(){
	bmpInfoHeader info;
	unsigned char *imagenRGB, *imagenGray, *imagenFiltrada;
	
	imagenRGB = abrirBMP("linux.bmp", &info);
	
	displayInfo( &info );
	printf("\n\n");
	imagenGray = reservarMemoria ( info.width, info.height );
	imagenFiltrada = reservarMemoria ( info.width, info.height );
	memset( imagenFiltrada, 255, info.width*info.height);
	
	
	RGBToGray( imagenRGB , imagenGray, info.width, info.height );
	
	//brilloImagen( imagenGray, info.width, info.height);


	width = info.width;
	height = info.height;	

	filtroPB( imagenGray, imagenFiltrada, info.width, info.height);
	//filtroPB( );
	
	GrayToRGB(imagenRGB, imagenFiltrada,info.width, info.height);
	
	guardarBMP("linuxGaussHilos.bmp",&info,imagenRGB);
	
	free( imagenRGB );
	free( imagenGray );
	free( imagenFiltrada );
	
	return 0;
}



