#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "SimpleMath.h"

//for a vol of 0.1 needs 5000 particles with 20 kernel particles

const int NUMBER_PARTICLES = 100;
const int NUM_KERNEL_PARTICLES = 10;
const double VOLUMEN = 0.1;
const double DENSITY_WATER = 998.29;

//const double PARTICLE_MASS = 1.0; 

//missing initial conditions for each particle. Calculate mass according to the density of the particle and the volumen
class Particle{

private:
	Vec3 position;
	Vec3 velocity;

	double mass;
	double density;
	double pressure;
	//double angle;
	//double life;
	//Vec3 acceleration;
	
	int label;//Numb. of the particle
	static int countParticles;//How many particles has been created
	static std::vector<Particle*> particles; //keep track of all created particles


public:
	Particle(Vec3 position, Vec3 velocity);
	Vec3 getPosition(){ return position; };
	Vec3 getVelocity(){ return velocity; };
	double getMass(){ return mass; };
	double getDensity(){ return density; };
	double getPressure(){ return pressure; };
	std::vector<Particle*> find_neighborhood(double  h);
	

};



	  


