#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "SimpleMath.h"


const int MAX_PARTICLES = 100;
const int NUM_NEIGHBOURING_PARTICLES = 10;
const double RADIUS = 0.1;
//const double PARTICLE_MASS = 1.0; 

//missing initial conditions for each particle. Calculate mass according to the density of the particle and the volumen
class Particle{

private:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	double mass;
	double density;
	double pressure;
	//double angle;
	//double life;
	
	int label;
	static int countParticles;
	static std::vector<Particle*> particles;


public:
	Particle(Vec3 position, Vec3 velocity, Vec3 acceleration);
	Vec3 getPosition(){ return position; };
	Vec3 getVelocity(){ return velocity; };
	double getMass(){ return mass; };
	double getDensity(){ return density; };
	double getPressure(){ return pressure; };
	std::vector<Particle*> find_neighborhood(double  h);
	

};



	  


