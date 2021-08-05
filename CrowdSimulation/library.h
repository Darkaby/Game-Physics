#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <iostream>

const float PI = 3.1415926535f;
const int CROWD_SIZE = 50;
const float STEP_TIME = 0.5f;
const float PERSON_SIZE = 0.8f;
const float PERSON_SPEED = 1.0f;
const float PERSON_LIMIT = PERSON_SIZE + 0.2f;
//Weight of the floor
const float FLOOR_SIZE = 20.0f;
//Height of the floor
const float FLOOR_HEIGHT = 10.0f;
//Deep of the floor
const float FLOOR_DEEP = 20.0f;


class Vect {
	private:
		float x0;
		float y0;
		float z0;

	public:
		Vect(float x1, float y1, float z1);

		float x();
		float y();
		float z();

};






class Person {
    private:
        float x0;
        float z0;
        float angle0;
        Vect* color0;

    public:
        Person(float x, float z, float angle);
        float x();
        float z();
        float angle();
        void setX(float x);
        void setZ(float z);
        void setAngle(float alpha);
        void setColor(float r, float g, float b);
        void draw();
        void advance();
};





class People {
    private:
        Person* crowd[CROWD_SIZE];
        bool intersectObject (float dx, float dz, float r);
        bool collision(float dx, float dz, float r, float vx, float vz);
        bool collisionWalls(Person* person);
    public:
        People();
        void drawCrowd();
		void collideWithObject(Person* person, float x, float z);
		void handleCollisions();
		void step();
};


#endif // LIBRARY_H_INCLUDED
