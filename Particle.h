#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "SimpleMath.h"


const int MAX_PARTICLES = 100;
const int NUM_NEIGHBOURING_PARTICLES = 10;
const double PI = 3.14159;
const double RADIUS = 0.1;
const double PARTICLE_MASS = 1.0; 


class Particle{

private:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	int label;
	double angle;
	double life;
	double density;
	double pressure;
	static int countParticles;
	static std::vector<Particle> particles;


public:
	Particle(Vec3 position, Vec3 velocity, Vec3 acceleration);
	Vec3 getPosition(){ return position; };
	std::vector<Particle> find_neighborhood(double  h);
	double applyKernelPoly6(Vec3 pos, double h);

};



	  


