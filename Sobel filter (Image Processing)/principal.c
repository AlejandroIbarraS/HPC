#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagen.h"
#include "defs.h"
#include "procesamiento.h"


unsigned char *imagenGray, *imagenSobel;
uint32_t width, height;

int main(){
	bmpInfoHeader info;
	unsigned char *imagenRGB;
	
	imagenRGB = abrirBMP("linux.bmp", &info);
	
	displayInfo( &info );
	printf("\n\n");

	imagenGray = reservarMemoria ( info.width, info.height );
	imagenSobel = reservarMemoria ( info.width, info.height );
	memset( imagenSobel, 255, info.width*info.height);
	
	RGBToGray( imagenRGB , imagenGray, info.width, info.height );
	
	width = info.width;
	height = info.height;

	Sobel(imagenGray, imagenSobel, info.width, info.height);
	//brilloImagen( imagenGray, info.width, info.height);

	GrayToRGB(imagenRGB, imagenSobel, info.width, info.height);
	
	guardarBMP("linuxSobel.bmp",&info,imagenRGB);
	
	free( imagenRGB );
	free( imagenGray );
	free( imagenSobel );
	
	return 0;
}



