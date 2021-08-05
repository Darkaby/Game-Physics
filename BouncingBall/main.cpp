#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "objects.h"

using namespace std;

Ball* ball;
Bouncing* bouncing;

//The rotation of the box
const float PI = 3.1415926535f;
//The radius of the ball
const float BALL_RADIUS = 1.5f;
const float OPACITY = 0.5f;

float randomFloat(int nmax) {
    return (float)rand() / ((float)RAND_MAX + 1) * nmax;
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND); //Enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-FLOOR_SIZE/2, -FLOOR_HEIGHT/2, -60.0f);
    glRotatef(50, 0.0f, 1.0f, 0.0f);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-FLOOR_DEEP, FLOOR_DEEP, 2 * FLOOR_DEEP, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//glRotatef(-_angle, 0.0f, 1.0f, 0.0f);


	ball->draw();

    glBegin(GL_QUADS);

    //Up
    glColor3f(0.0f, 1.0f, 2.0f);
	glVertex3f(0.0f, FLOOR_HEIGHT, FLOOR_DEEP);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, FLOOR_DEEP);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, 0.0f);
	glVertex3f(0.0f, FLOOR_HEIGHT, 0.0f);

	//Right
	glColor3f(2.0f, 2.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, 0.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, 0.0f);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, FLOOR_DEEP);
	glVertex3f(FLOOR_SIZE, 0.0f, FLOOR_DEEP);

	//Bottom
	glColor3f(0.0f, 1.0f, 2.0f);
	glVertex3f(0.0f, 0.0f, FLOOR_DEEP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, 0.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, 0.0f, FLOOR_DEEP);

	//Back
	glColor3f(2.0f, 0.0f, 2.0f);
	glVertex3f(0.0f, FLOOR_HEIGHT, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, 0.0f, 0.0f);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, 0.0f);

	//Left
	glColor4f(1.0f, 1.0f, 0.0f, OPACITY);
	glVertex3f(0.0f, FLOOR_HEIGHT, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, FLOOR_DEEP);
	glVertex3f(0.0f, FLOOR_HEIGHT, FLOOR_DEEP);

	//Front
	glColor4f(1.0f, 0.0f, 1.0f, OPACITY);
	glVertex3f(0.0f, FLOOR_HEIGHT, FLOOR_DEEP);
	glVertex3f(0.0f, 0.0f, FLOOR_DEEP);
	glVertex3f(FLOOR_SIZE, 0.0f, FLOOR_DEEP);
	glVertex3f(FLOOR_SIZE, FLOOR_HEIGHT, FLOOR_DEEP);

    glEnd();

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {

	bouncing->step();

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Bouncing Ball");
	initRendering();

	ball = new Ball(randomFloat(FLOOR_SIZE - BALL_RADIUS), randomFloat(FLOOR_HEIGHT - BALL_RADIUS),
                    randomFloat(FLOOR_DEEP - BALL_RADIUS), randomFloat(2 * PI), randomFloat(2 * PI));
	bouncing = new Bouncing(ball);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}
