// **********************************************************************
//	FirstTexture.cpp   --   Exemplo de mapeamento de texturas.
//		
//		Este programa foi criado a partir de um fonte obtido em 
//	http://nehe.gamedev.net, na "Lesson 06"
//
//		
//
//
//
// **********************************************************************

#include <windows.h>
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tgaload.h"

// Qtd máxima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 1

#define TEXTURA_FUNDO 0

// vetor com os números das texturas
GLuint texture_id[MAX_NO_TEXTURES];

float xrot;
float yrot;
float zrot;
float ratio;


// **********************************************************************
//  void initTexture(void)
//		Define a textura a ser usada 
//
// **********************************************************************
void initTexture (void)
{

	// Habilita o uso de textura 
	glEnable ( GL_TEXTURE_2D );

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Define quantas texturas serão usadas no programa 
	glGenTextures (1, texture_id);  // 1 = uma textura;
									// texture_id = vetor que guardas os números das texturas

	// Define o número da textura do cubo.
	texture_id[TEXTURA_FUNDO] = 1001;

	// Define que tipo de textura será usada
	// GL_TEXTURE_2D ==> define que será usada uma textura 2D (bitmaps)
	// texture_id[CUBE_TEXTURE]  ==> define o número da textura 
	glBindTexture ( GL_TEXTURE_2D, texture_id[TEXTURA_FUNDO] );

	// carrega a uma imagem TGA 
	image_t temp_image;
	tgaLoad  ( "cosmos2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

}
// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glEnable ( GL_COLOR_MATERIAL );
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	
	glEnable ( GL_CULL_FACE );
	
}

// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(80,ratio,1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30,
		      0,0,10,
			  0.0f,1.0f,0.0f);
}

// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity ( );
	glPushMatrix();
	glTranslatef ( 0.0, 0.0, -5.0 );
	/*glRotatef ( xrot, 1.0, 0.0, 0.0 );
	glRotatef ( yrot, 0.0, 1.0, 0.0 );
	glRotatef ( zrot, 0.0, 0.0, 1.0 );*/

	// define qual das texturas usar
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	
	glBegin ( GL_QUADS );
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -1.8f,  3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 3.0f, -1.8f,  3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.0f,  1.8f,  3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f,  1.8f,  3.0f);

	glEnd();
	
	glPopMatrix();
	xrot+=0.3f;
	yrot+=0.2f;
	zrot+=0.4f;
	glutSwapBuffers();
}



// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main (int argc, char** argv  )   {

	glutInit            ( &argc, argv );
	glutInitDisplayMode ( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); 
	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 900, 680 );
	glutCreateWindow    ( "Tópicos em Computação Gráfica - Teste com Texturas." ); 
		
	init ();
	initTexture ();
		
	glutDisplayFunc ( display );  
	glutReshapeFunc ( reshape );
	glutIdleFunc ( display );
	glutMainLoop ( );

	return 0;
}




