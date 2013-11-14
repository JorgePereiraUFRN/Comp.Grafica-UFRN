/*
 * TelaFundo.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: Jorge
 */

#include "TelaFundo.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "Textura.h"

//para definir o 'campo' do jogo, representando cada canto
#define MINIMO_X -14
#define MAXIMO_X 14
#define MINIMO_Y -14
#define MAXIMO_Y 14

namespace Fundo {



TelaFundo::TelaFundo() {

}

TelaFundo::~TelaFundo() {
	// TODO Auto-generated destructor stub
}


void TelaFundo:: carregar(){

}


void desenhaFundo(){

	Textura * texturaFundo = new Textura();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texturaFundo->texID);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0.0,0.0);
            glVertex3i(MINIMO_X*5,MAXIMO_Y*5,-50);
            glTexCoord2f(1.0,0.0);
            glVertex3i(MINIMO_X*5,MINIMO_Y*5,-50);
            glTexCoord2f(1.0,1.0);
            glVertex3i(MAXIMO_X*5,MINIMO_Y*5,-50);
            glTexCoord2f(0.0,1.0);
            glVertex3i(MAXIMO_X*5,MAXIMO_Y*5, -50);
        glEnd();
    glPopMatrix();
}


void desenha()//desenha os itens do jogo.
{
    //limpa os buffers de cor e profundidade.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            desenhaFundo();
            //desenha a nave na posição atual dela.
            glPushMatrix();

            glPopMatrix();


}



} /* namespace Fundo */
