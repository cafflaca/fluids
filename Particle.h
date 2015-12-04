#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "SimpleMath.h"

// Initial particle block dimensions
const double PARTICLE_BLOCK_LENGTH  = 10.0;
const double PARTICLE_BLOCK_WIDTH   = 10.0;
const double PARTICLE_BLOCK_HEIGHT  = 10.0;
const double PARTICLE_RADIUS        = 0.05;

//for a vol of 0.1 needs 5000 particles with 20 kernel particles

const int NUMBER_PARTICLES = 100;
const int NUM_KERNEL_PARTICLES = 20;
const double VOLUMEN = 0.1;
const double DENSITY_WATER = 998.29;
const double MASS = DENSITY_WATER*VOLUMEN / NUMBER_PARTICLES;

//const double PARTICLE_MASS = 1.0; 

//missing initial conditions for each particle. Calculate mass according to the density of the particle and the volumen
class Particle{

private:

	double mass;
	double density;
	
	//double angle;
	//double life;
	//Vec3 acceleration;

public:
    
    Vec3 position;
    Vec3 velocity;
    Vec3 force_densities;
    
    double pressure;
    
    int label;//Numb. of the particle
    static int countParticles;//How many particles has been created
    static std::vector<Particle*> particles; //keep track of all created particles
    
	Particle(Vec3 position, Vec3 velocity);
	Vec3 getPosition(){ return position; };
	Vec3 getVelocity(){ return velocity; };
    void setPosition(Vec3 p){ position = p; };
    void setVelocity(Vec3 v){ velocity = v; };
    void setDensity(double d){ density = d; };
    void setPressure(double p){ pressure = p; };
	double getMass(){ return mass; };
	double getDensity(){ return density; };
	double getPressure(){ return pressure; };
	std::vector<Particle*> find_neighborhood(double  h);
	

};



	  


