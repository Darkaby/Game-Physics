#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

const float CUBE_SIZE = 6.0f;
const int NB_PARTICLES_AXIS = 21;
const float PARTICLE_SIZE = CUBE_SIZE / (NB_PARTICLES_AXIS - 1);
const float STEP_TIME = 0.05f;
const float PARTICLE_TIME_TO_LIVE = 80;

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





class Particle {
	private:
        float x0, y0, z0;
        float xFirst, yFirst, zFirst;
        float speed0;
		float size0;
		float timeAlive = 0;
		float life_span;
		bool alive = true;
		Vect* color0;
		Vect* normal0;

		Vect* normalize();

	public:
		Particle (float size1);
		Particle (float x1, float y1, float z1, float t);

        float x();
		float y();
		float z();
		float pSize();
		bool isAlive();
        float timeLeft();

        void setColor(float r, float g, float b);
        void setSpeed(float s);
        void posBegin();
		void draw();
		void advance();
};

#endif
