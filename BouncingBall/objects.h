#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <vector>

//Weight of the floor
const float FLOOR_SIZE = 40.0f;
//Height of the floor
const float FLOOR_HEIGHT = 30.0f;
//Deep of the floor
const float FLOOR_DEEP = 30.0f;

//Represents a single ball
class Ball {
	private:
		//The radius of the ball
		float r;
		//The x coordinate of the ball
		float x0;
		//The y coordinate of the ball
		float y0;
		//The z coordinate of the ball
		float z0;
		//The angle at which the ball is traveling.  An angle of 0 indicates the
		//positive x direction, while an angle of PI / 2 indicates the positive
		//z direction.  The angle is always between 0 and 2 * PI.
		float angle_theta;
		float angle_phi;


	public:
		//Constructs a new ball with the specified radius, x and z coordinates,
		//and angle of travel.  An angle of 0 indicates the positive x
		//direction, while an angle of PI / 2 indicates the positive z
		//direction.  The angle must be between 0 and 2 * PI.
		Ball(float x1, float y1, float z1, float angle1, float angle2);

		//Returns the radius of the ball
		float radius();
		//Returns the x coordinate of the ball
		float x();
		//Returns the y coordinate of the ball
		float y();
		//Returns the z coordinate of the ball
		float z();
		//Returns the angle at which the ball is traveling.  An angle of 0
		//indicates the positive x direction, while an angle of PI / 2 indicates
		//the positive z direction.  The returned angle is between 0 and 2 * PI.
		float angleTheta();
		float anglePhi();
		//Sets the angle at which the ball is traveling.  An angle of 0
		//indicates the positive x direction, while an angle of PI / 2 indicates
		//the positive z direction.  The angle must be between 0 and 2 * PI.
		void setAngleTheta(float angle1);
		void setAnglePhi(float angle2);
		//Advances the state of the ball by the specified amount of time
		void advance(float dt);
		// Draw a ball
		void draw();

};

class Bouncing {
    private:
        Ball* ball0;
        bool intersectObject (float dx, float dy, float dz, float r);

    public:
        Bouncing (Ball* ball);

		bool collisionFloor();
		void collideWithFloor(float x, float y, float z);
		void handleCollisions();
        void step();
};

#endif // OBJECTS_H_INCLUDED
