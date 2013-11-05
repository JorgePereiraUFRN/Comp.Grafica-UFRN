#include <GL/glut.h>

static GLfloat year = 0, day = 0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0,0,5,0,0,0,0,1,0);

	glPushMatrix();
		glutWireSphere(1, 20, 16);
		glRotatef(year, 0, 1, 0);
		glTranslatef(2, 0, 0);
		glRotatef(day, 0, 1, 0);
		glutWireSphere(0.2, 10, 8);
	glPopMatrix();

	glFlush();
}

void reshape (int w, int h) {
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,1.5,20);
	glMatrixMode(GL_MODELVIEW);
}

void inicializa(void) {
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 'd':
			day = (day + 10);
			break;
		case 'D':
			day = (day - 10);
			break;
		case 'y':
			year = (year + 10);
			break;
		case 'Y':
			year = (year - 10);
			break;
	}
	glutPostRedisplay();
}

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Primeiro Programa");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	inicializa();
	glutMainLoop();
	return 0;
}
