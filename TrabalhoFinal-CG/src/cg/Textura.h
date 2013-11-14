/*
 * Textura.h
 *
 *  Created on: Nov 14, 2013
 *      Author: Jorge
 */




typedef unsigned char   GLubyte;        /* 1-byte unsigned */
typedef unsigned int    GLuint;         /* 4-byte unsigned */

class Textura {
public:
	GLubyte* imageData;						// Image Data (Up To 32 Bits)
	GLuint bpp;							// Image Color Depth In Bits Per Pixel
	GLuint width;											// Image Width
	GLuint height;											// Image Height
	GLuint texID;						// Texture ID Used To Select A Texture
	GLuint type;

	Textura();
	~Textura();


};


