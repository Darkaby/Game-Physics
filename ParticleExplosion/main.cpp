#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "particle.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

const int NB_PARTICLES = NB_PARTICLES_AXIS * NB_PARTICLES_AXIS * NB_PARTICLES_AXIS;
const int START_TIME = 30;
int t = 0;

Particle* particules[NB_PARTICLES];
Particle* particule_lamda;

float randomFloat(int nmax) {
    return (float)rand() / (float)RAND_MAX * nmax;
}

float randomSpeed() {
    int r = rand()%10;
    switch (r){
        case 0:
            return 0.05;
        case 1:
            return 0.06;
        case 2:
            return 0.07;
        case 3:
            return 0.08;
        case 4:
            return 0.09;
        case 5:
            return 0.1;
        case 6:
            return 0.11;
        case 7:
            return 0.12;
        case 8:
            return 0.13;
        case 9:
            return 0.14;
    }
}

void initCube(Particle* particule) {
    int i = 0;
    for (float x = -CUBE_SIZE/2; x <= CUBE_SIZE/2; x += particule->pSize()) {
        for (float y = -CUBE_SIZE/2; y <= CUBE_SIZE/2; y += particule->pSize()) {
            for (float z = -CUBE_SIZE/2; z <= CUBE_SIZE/2; z += particule->pSize()) {

                    particules[i] = new Particle(x, y, z, randomFloat(PARTICLE_TIME_TO_LIVE));
                    particules[i]->setColor(randomFloat(2), randomFloat(2), randomFloat(2));
                    particules[i]->setSpeed(randomSpeed());
                    i++;
            }
        }
    }
}

void drawCube(){
    for (int i = 0; i < NB_PARTICLES; i++) {
        particules[i]->draw();
    }
}

void explode() {
    for (int i = 0; i < NB_PARTICLES; i++) {
        particules[i]->advance();

        if (!particules[i]->isAlive()) {
            printf("Particle %d dead; ", i);
            particules[i]->posBegin();

        }
    }
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0f;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -70.0f);

	//Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glRotatef(_angle, 0.0f, 1.0f, 0.0f);

    drawCube();

	glutSwapBuffers();
}

void update(int value) {
    _angle += 1.0f;
    if (_angle > 360) {
            _angle -= 360;
    }

    t++;
    if (t > START_TIME) {
        explode();
    }

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("Lighting - videotutorialsrock.com");
	initRendering();

    particule_lamda = new Particle(PARTICLE_SIZE);
    initCube(particule_lamda);
    printf("InitCube. \t");

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
