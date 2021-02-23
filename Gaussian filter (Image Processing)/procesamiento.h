#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height);
unsigned char * reservarMemoria( uint32_t width, uint32_t height);
void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height );
void filtroPB(unsigned char *imagenG, unsigned char *imagenF, uint32_t width, uint32_t height);

#endif
