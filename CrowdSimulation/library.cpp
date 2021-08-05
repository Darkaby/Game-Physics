#include <iostream>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "library.h"


float randomFloat(int nmax) {
    return (float)rand() / (float)RAND_MAX * nmax;
}

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







Person::Person(float x, float z, float angle) {
    x0 = x;
    z0 = z;
    angle0 = angle;
}

float Person::x() {
    return x0;
}

float Person::z() {
    return z0;
}

float Person::angle() {
    return angle0;
}

void Person::setX(float x) {
    x0 = x;
}

void Person::setZ(float z) {
    z0 = z;
}

void Person::setAngle(float alpha) {
    angle0 = alpha;
}

void Person::setColor(float r, float g, float b){
    color0 = new Vect(r, g, b);
}

void Person::draw() {

    glColor3f(color0->x(), color0->y(), color0->z());
    //Head
    glPushMatrix();
    glTranslatef(x0, 2.5f, z0);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    //Body
    glPushMatrix();
    glTranslatef(x0, 1.0f, z0);
    glScalef(PERSON_SIZE, 2.0f, PERSON_SIZE);
    glutSolidCube(1);
    glPopMatrix();
}

void Person::advance() {
    x0 += STEP_TIME * cos(angle0) * PERSON_SPEED;
	z0 += STEP_TIME * sin(angle0) * PERSON_SPEED;
}







People::People() {
    for (int i = 0; i < CROWD_SIZE; i++) {
        crowd[i] = new Person (randomFloat(FLOOR_SIZE*2), randomFloat(FLOOR_DEEP*2), randomFloat(2 * PI));
        crowd[i]->setColor(randomFloat(2), randomFloat(2), randomFloat(2));
    }
}

void People::drawCrowd() {
    for (int i = 0; i < CROWD_SIZE; i++) {
        crowd[i]->draw();
    }
}

bool People::intersectObject (float dx, float dz, float r) {
    return dx * dx + dz * dz < r * r;
}

bool People::collision(float dx, float dz, float r, float vx, float vz) {
    return intersectObject(dx, dz, r) && vx * dx + vz * dz > 0;
}

bool People::collisionWalls(Person* person) {
    if (((person->x() - PERSON_LIMIT > 0) && (person->x() + PERSON_LIMIT < FLOOR_SIZE * 2))
        && ((person->z() - PERSON_LIMIT > 0) && (person->z() + PERSON_LIMIT < FLOOR_DEEP * 2))
        && !intersectObject(FLOOR_SIZE * 2 - person->x(), FLOOR_DEEP * 2 - person->z(), PERSON_LIMIT))
        return false;
    else
        return true;
}

void People::collideWithObject(Person* person, float x, float z) {
    float dx = x - person->x();
    float dz = z - person->z();
    float normal = atan2(-dz, -dx);

    float newAngle = 2 * normal - PI - person->angle();
    if (newAngle < 0) {
        newAngle += 2 * PI;
    }
    else if (newAngle > 2 * PI) {
        newAngle -= 2 * PI;
    }

    person->setAngle(newAngle);
}

void People::handleCollisions() {
    for (int i = 0; i < CROWD_SIZE; i++) {
        Person* person = crowd[i];

        // Person - wall collisions
        for(float x = 0; x < FLOOR_SIZE * 2; x += 1.0) {
            for (float z = 0; z < FLOOR_DEEP * 2; z += 1.0) {
                if (collisionWalls(person)) {
                    collideWithObject(person, x, z);
                }
            }
        }

        // Person-person collisions
        for(int j = i + 1; j < CROWD_SIZE; j++) {
			Person* person2 = crowd[j];
			if (collision(person2->x() - person->x(), person2->z() - person->z(), PERSON_LIMIT * 2,
                          PERSON_SPEED * (cos(person->angle()) - cos(person2->angle())),
                          PERSON_SPEED * (sin(person->angle()) - sin(person2->angle())))) {
				collideWithObject(person, person2->x(), person2->z());
				collideWithObject(person2, person->x(), person->z());
			}
		}
    }
}

void People::step() {
    for (int i = 0; i < CROWD_SIZE; i++) {
        crowd[i]->advance();
        handleCollisions();

        if (crowd[i]->x() > FLOOR_SIZE * 2)
            crowd[i]->setX(crowd[i]->x() - FLOOR_SIZE * 2);
        else if (crowd[i]->x() < 0)
            crowd[i]->setX(crowd[i]->x() + FLOOR_SIZE * 2);

        if (crowd[i]->z() > FLOOR_DEEP * 2)
            crowd[i]->setZ(crowd[i]->z() - FLOOR_DEEP * 2);
        else if (crowd[i]->z() < 0)
            crowd[i]->setZ(crowd[i]->z() + FLOOR_DEEP * 2);

    }
}
