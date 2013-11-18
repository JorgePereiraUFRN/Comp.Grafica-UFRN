// **********************************************************************
//	SecondTexture.cpp   --   Exemplo de mapeamento de texturas.
//		
//		Este programa foi criado a partir de um fonte obtido em 
//	http://nehe.gamedev.net, na "Lesson 06"
//
//
// **********************************************************************

#include <windows.h>
#include <stdio.h>
#include <GL\glu.h>
#include <GL/glut.h>
#include "tgaload.h"
#include "image.h"
#include <math.h>

#define PI 3.1415

#define COORD_TEXTURA_AVIAO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_AVIAO 0.3,0.52,0.18,1.0
#define TEXTURA_DO_AVIAO "camuflagem.rgb"

GLint WIDTH = 800;
GLint HEIGHT = 600;

GLfloat obs[3] = { 0.0, -17.0, 0.0 };
GLfloat look[3] = { 0.0, 3.0, 0.0 };
GLuint textura_plano;
GLuint textura_aviao;

GLshort texturas = 1;
GLfloat tetaxz = 90;
GLfloat raioxz = 3;
GLuint jato;

GLfloat cta[4][2] = { { -COORD_TEXTURA_AVIAO, -COORD_TEXTURA_AVIAO }, {
		+COORD_TEXTURA_AVIAO, -COORD_TEXTURA_AVIAO }, { +COORD_TEXTURA_AVIAO,
		+COORD_TEXTURA_AVIAO }, { -COORD_TEXTURA_AVIAO, +COORD_TEXTURA_AVIAO } };

// Qtd máxima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 8

#define METEORO1 1
#define METEORO2  2
#define FUNDO 0
#define METEORO3 3
#define METEORO4 4
#define METEORO5 5

// vetor com os números das texturas
GLuint texture_id[MAX_NO_TEXTURES];

float xrot;
float yrot;
float zrot;
float ratio;

int posicao_metoeoro1 = 0;
int posicao_metoeoro2 = 100;
int posicao_metoeoro3 = 300;
int posicao_metoeoro4 = 400;
int posicao_metoeoro5 = 500;

float t1 = 0;
float t2 = 0.2;
float t3 = 0.3;
float t4 = 0.4;
float t5 = 0.5;

void compoe_jato(void) {
	GLUquadricObj *quadric;

	GLfloat asa[][3] = { { -4.0, 0.0, 0.0 }, { +4.0, 0.0, 0.0 },
			{ 0.0, 0.0, 3.0 } };

	GLfloat cauda[][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 2.0, -1.0 }, { 0.0, 2.0,
			0.0 }, { 0.0, 0.0, 2.0 } };
	/* inicia a composicao do jato */
	jato = glGenLists(1);
	glNewList(jato, GL_COMPILE);

	/* asas */
	glBegin(GL_TRIANGLES);
	glTexCoord2fv(cta[0]);
	glVertex3fv(asa[0]);
	glTexCoord2fv(cta[1]);
	glVertex3fv(asa[1]);
	glTexCoord2fv(cta[3]);
	glVertex3fv(asa[2]);
	glEnd();

	/* corpo */
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluCylinder(quadric, 0.5, 0.5, 4, 12, 3);

	/* nariz */
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	glPushMatrix();
	glTranslatef(0, 0, 4);
	gluCylinder(quadric, 0.5, 0.0, 1.5, 12, 3);
	glPopMatrix();

	/* cauda */
	glBegin(GL_POLYGON);
	glTexCoord2fv(cta[0]);
	glVertex3fv(cauda[0]);
	glTexCoord2fv(cta[1]);
	glVertex3fv(cauda[1]);
	glTexCoord2fv(cta[2]);
	glVertex3fv(cauda[2]);
	glTexCoord2fv(cta[3]);
	glVertex3fv(cauda[3]);
	glEnd();

	/* cabine do piloto */
	glTranslatef(0, 0.3, 3.5);
	glPushMatrix();
	glScalef(0.7, 0.7, 2.0);
	quadric = gluNewQuadric();
	glColor3f(0.3, 0.5, 1);
	//glDisable(GL_TEXTURE_2D);
	gluSphere(quadric, 0.5, 12, 12);
	glPopMatrix();

	/* termina a composicao do jato*/
	glEndList();
}

// **********************************************************************
//  void initTexture(void)
//		Define a textura a ser usada 
//
// **********************************************************************
void initTexture(void) {

	image_t temp_image; // variável que irá armazenar a textura a ser usada

	// Habilita o uso de textura 
	glEnable( GL_TEXTURE_2D);

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

	// Define quantas texturas serão usadas no programa 
	glGenTextures(1, texture_id);  // 1 = uma textura;
								   // texture_id = vetor que guardas os números das texturas

	// Define os números da textura dos cubos
	texture_id[FUNDO] = 1000;
	texture_id[METEORO1] = 1001;
	texture_id[METEORO2] = 1002;
	texture_id[METEORO3] = 1003;
	texture_id[METEORO4] = 1004;
	texture_id[METEORO5] = 1005;

	// ****
	// Define a textura do objeto da ESQUERDA
	// ****
	glBindTexture( GL_TEXTURE_2D, texture_id[FUNDO]);
	tgaLoad("cosmos2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	// Define que tipo de textura será usada
	// GL_TEXTURE_2D ==> define que será usada uma textura 2D (bitmaps)
	// texture_id[OBJETO_ESQUERDA]  ==> define o número da textura 
	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO1]);
	// Carrega a primeira imagem .TGA 
	tgaLoad("TCG1.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	// ****
	// Define a textura do objeto da DIREITA
	// ****

	// Define que tipo de textura será usada
	// GL_TEXTURE_2D ==> define que será usada uma textura 2D (bitmaps)
	// texture_id[OBJETO_ESQUERDA]  ==> define o número da textura 
	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO2]);

	// carrega a segunda imagem TGA
	tgaLoad("gremio2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO3]);

	// carrega a segunda imagem TGA
	tgaLoad("gremio2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO3]);

	// carrega a segunda imagem TGA
	tgaLoad("gremio2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO4]);

	// carrega a segunda imagem TGA
	tgaLoad("gremio2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture( GL_TEXTURE_2D, texture_id[METEORO5]);

	// carrega a segunda imagem TGA 
	tgaLoad("gremio2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

}

void carregar_texturas(void) {
	IMAGE *img;
	GLenum gluerr;

	/* textura do aviao */
	glGenTextures(1, &textura_aviao);
	glBindTexture(GL_TEXTURE_2D, textura_aviao);

	if (!(img = ImageLoad(TEXTURA_DO_AVIAO))) {
		fprintf(stderr, "Error reading a texture.\n");
		exit(-1);
	}

	gluerr = gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY,
	GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *) (img->data));
	if (gluerr) {
		fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
		exit(-1);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void) {

	carregar_texturas();
	compoe_jato();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glEnable( GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable( GL_CULL_FACE);
}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(80, ratio, 1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30, 0, 0, 10, 0.0f, 1.0f, 0.0f);
}

void displayFundo(void) {
//	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//	glLoadIdentity ( );
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	/*glRotatef ( xrot, 1.0, 0.0, 0.0 );
	 glRotatef ( yrot, 0.0, 1.0, 0.0 );
	 glRotatef ( zrot, 0.0, 0.0, 1.0 );*/

	// define qual das texturas usar
	glBindTexture( GL_TEXTURE_2D, texture_id[FUNDO]);

	glBegin( GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, -1.8f, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(3.0f, -1.8f, 3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 1.8f, 3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.0f, 1.8f, 3.0f);

	glEnd();
	glPopMatrix();

}

// **********************************************************************
//   void DesenhaCubo (GLuint nro_da_textura)
//
//
// **********************************************************************
void DesenhaCubo(GLuint nro_da_textura) {
	// Desenha Cubo 1

	// define qual das texturas usar
	glBindTexture( GL_TEXTURE_2D, nro_da_textura);

	glBegin( GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

}

// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display(void) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	displayFundo();

	glPushMatrix();
	posicao_metoeoro1 = (posicao_metoeoro1++) % 95;
	posicao_metoeoro2 = (posicao_metoeoro2++) % 95;
	posicao_metoeoro3 = (posicao_metoeoro3++) % 95;
	posicao_metoeoro4 = (posicao_metoeoro4++) % 95;
	posicao_metoeoro5 = (posicao_metoeoro5++) % 95;

	t1 += 0.02;
	t2 += 0.02;
	t3 += 0.02;
	t4 += 0.02;
	t5 += 0.02;



	glTranslatef(0.0, 50 + t1 * (-51.5), -100 + 95 * t1);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	DesenhaCubo(texture_id[METEORO1]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(+3.0, 50 + t2 * (-51.5), -100 + 95 * t2);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	DesenhaCubo(texture_id[METEORO2]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(+5.0, 50 + t3 * (-51.5), -100 + 95 * t3);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	DesenhaCubo(texture_id[METEORO3]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, 50 + t4 * (-51.5), -100 + 95 * t4);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	DesenhaCubo(texture_id[METEORO4]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 50 + t5 * (-51.5), -100 + 95 * t5);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glRotatef(zrot, 0.0, 0.0, 1.0);

	DesenhaCubo(texture_id[METEORO5]);

	glPopMatrix();

	//======================== jato
	glTranslatef(0.0, -10.0, 2.0);
	// glPushMatrix();

	/* calcula a posicao do observador */
	obs[0] = raioxz * cos(2 * PI * tetaxz / 360);
	obs[2] = raioxz * sin(2 * PI * tetaxz / 360);
	gluLookAt(obs[0], obs[1], obs[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

	/* habilita/desabilita uso de texturas*/
	/*  if(texturas){
	 glEnable(GL_TEXTURE_2D);
	 }
	 else{
	 glDisable(GL_TEXTURE_2D);
	 }*/

	glColor4f(COR_DO_AVIAO);
	glBindTexture(GL_TEXTURE_2D, textura_aviao);
	glCallList(jato);

	if (t1 >= 1.0) {
		t1 = 0.0;
	}
	if (t2 >= 1.0) {
		t2 = 0.0;
	}
	if (t3 >= 1.0) {
		t3 = 0.0;
	}
	if (t4 >= 1.0) {
		t4 = 0.0;
	}
	if (t5 >= 1.0) {
		t5 = 0.0;
	}

	xrot += 0.2f;
	yrot += 0.1f;
	zrot += 0.3f;
	glutSwapBuffers();
}

void special(int key, int x, int y) {
	switch (key) {
	/* case GLUT_KEY_UP:
	 obs[1]=obs[1]+1;
	 glutPostRedisplay();
	 break;
	 case GLUT_KEY_DOWN:
	 obs[1] =obs[1]-1;
	 glutPostRedisplay();
	 break;*/
	case GLUT_KEY_LEFT:
		tetaxz = tetaxz - 2;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		tetaxz = tetaxz + 2;

		glutPostRedisplay();
		break;

		printf("%f", tetaxz);
	}
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:        // When Escape Is Pressed...
		exit(0);   // Exit The Program
		break;        // Ready For Next Case
	default:        // Now Wrap It Up
		break;
	}
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )  
//
//
// **********************************************************************
void arrow_keys(int a_keys, int x, int y) {
	switch (a_keys) {
	case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		glutFullScreen(); // Go Into Full Screen Mode
		break;
	case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutInitWindowSize(700, 500);
		break;
	default:
		break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Tópicos em Computação Gráfica - Teste com Texturas.");

	init();
	initTexture();

	//glutDisplayFunc ( displayFundo );
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(arrow_keys);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}

