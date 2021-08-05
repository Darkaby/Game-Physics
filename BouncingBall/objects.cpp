#include <cmath>
#include <cstdlib>
#include <math.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "objects.h"

using namespace std;

namespace {
	const float PI = 3.1415926535f;
	//The radius of the ball
	const float BALL_RADIUS = 1.5f;
	//The speed of the ball
	const float BALL_SPEED = 1.0f;
	//const float BALL_MASS = 0.2f;
	//const float BALL_HEIGHT = 6.0f;
	//The amount of time by which the state of the game is advanced in each call
	//to the game's step() method
	const float STEP_TIME = 0.4f;
}


Ball::Ball(float x1, float y1, float z1, float angle1, float angle2) {
	r = BALL_RADIUS;
	x0 = x1;
	y0 = y1;
	z0 = z1;
	angle_theta = angle1;
	angle_phi = angle2;
}

float Ball::radius() {
	return r;
}

float Ball::x() {
	return x0;
}

float Ball::y() {
	return y0;
}

float Ball::z() {
	return z0;
}

float Ball::angleTheta() {
	return angle_theta;
}

float Ball::anglePhi() {
	return angle_phi;
}

void Ball::setAngleTheta(float angle1) {
	angle_theta = angle1;
}

void Ball::setAnglePhi(float angle2) {
	angle_phi = angle2;
}

void Ball::advance(float dt) {
	//Advance the position of the ball
	x0 += dt * sin(angle_phi) * sin(angle_theta) * BALL_SPEED;
	y0 += dt * cos(angle_phi) * BALL_SPEED;
	z0 += dt * sin(angle_phi) * cos(angle_theta) * BALL_SPEED;

}

void Ball::draw() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x0, y0, z0);
    glutSolidSphere(r, 20, 20);
    glPopMatrix();
}






Bouncing::Bouncing(Ball* ball) {
    ball0 = ball;
}

void Bouncing::step() {
    ball0->advance(STEP_TIME);
    handleCollisions();
}

bool Bouncing::intersectObject (float dx, float dy, float dz, float r) {
    return dx * dx + dy * dy + dz * dz < r * r;
}

bool Bouncing::collisionFloor() {
    if (((ball0->y() - ball0->radius() > 0.0) && (ball0->y() + ball0->radius() < FLOOR_HEIGHT - 0.12))
        && ((ball0->x() - ball0->radius() > 0.0) && (ball0->x() + ball0->radius() < FLOOR_SIZE))
        && ((ball0->z() - ball0->radius() > 0.0) && (ball0->z() + ball0->radius() < FLOOR_DEEP)))
        return false;
    else
        return true;
}

//Returns the resultant angle when an object traveling at an angle of angle
//bounces off of a wall whose normal is at an angle of normal.  The returned
//angle will be between 0 and 2 * PI.  An angle of 0 indicates the positive
//x direction, and an angle of PI / 2 indicates the positive z direction.
void Bouncing::collideWithFloor(float x, float y, float z) {
    float dx = x - ball0->x();
    float dy = y - ball0->y();
    float dz = z - ball0->z();
    float normalz = atan2(-dx, -dy);
    float normaly = atan2(-dz, -dx);

    float newAnglePhi = 2 * normalz - PI - ball0->anglePhi();
    if (newAnglePhi < 0) {
        newAnglePhi += 2 * PI;
    }
    else if (newAnglePhi > 2 * PI) {
        newAnglePhi -= 2 * PI;
    }

    float newAngleTheta = 2 * normaly - PI - ball0->angleTheta();
    if (newAngleTheta < 0) {
        newAngleTheta += 2 * PI;
    }
    else if (newAngleTheta > 2 * PI) {
        newAngleTheta -= 2 * PI;
    }

    ball0->setAnglePhi(newAnglePhi);
    ball0->setAngleTheta(newAngleTheta);
}

void Bouncing::handleCollisions() {
    for(float x = 0; x < FLOOR_SIZE; x += 0.7) {
        for(float y = 0; y < FLOOR_HEIGHT; y += 0.7) {
            for (float z = 0; z < FLOOR_DEEP; z += 0.7) {
                if (collisionFloor() && intersectObject(x - ball0->x(), y - ball0->y(), z - ball0->z(), BALL_RADIUS + 0.15)) {
                    collideWithFloor(x, y, z);
                }
            }
        }
    }
}
