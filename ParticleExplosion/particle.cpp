#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>

#include "particle.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

Vect::Vect(float x1, float y1, float z1) {
    x0 = x1;
    y0 = y1;
    z0 = z1;
}

float Vect::x(){
    return x0;
}

float Vect::y(){
    return y0;
}

float Vect::z(){
    return z0;
}






Particle::Particle(float size1){
    size0 = size1;
}

Particle::Particle(float x1, float y1, float z1, float t) {
    xFirst = x1;
    yFirst = y1;
    zFirst = z1;

    x0 = x1;
    y0 = y1;
    z0 = z1;

    life_span = t;
    normal0 = normalize();
}

float Particle::pSize(){
    return size0;
}

float Particle::x() {
    return x0;
}

float Particle::y() {
    return y0;
}

float Particle::z() {
    return z0;
}

bool Particle::isAlive() {
    return alive;
}

float Particle::timeLeft() {
    return life_span - timeAlive;
}

void Particle::setColor(float r, float g, float b){
    color0 = new Vect(r, g, b);
}

void Particle::setSpeed(float s) {
    speed0 = s;
}

void Particle::posBegin() {
    x0 = xFirst;
    y0 = yFirst;
    z0 = zFirst;
    timeAlive = 0;
}

void Particle::draw(){
    glPushMatrix();
    glTranslatef(x0, y0, z0);
    glColor3f(color0->x(), color0->y(), color0->z());
    glutSolidCube(PARTICLE_SIZE);
    glPopMatrix();
}

Vect* Particle::normalize() {
    float m = sqrt(x0 * x0 + y0 * y0 + z0 * z0);
	return new Vect(x0 / m, y0 / m, z0 / m);
}

void Particle::advance() {

    x0 += normal0->x() * speed0;
    y0 += normal0->y() * speed0;
    z0 += normal0->z() * speed0;
    timeAlive += speed0;

    if (timeLeft() < 0 || (x0 > 50 || x0 < -50 || y0 > 40 || y0 < -40 || z0 > 50)) {
        alive = false;
        }
    else
        alive = true;
}
