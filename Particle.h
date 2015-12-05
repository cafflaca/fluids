#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "SimpleMath.h"

// Initial particle block dimensions
const double PARTICLE_BLOCK_LENGTH  = 10.0;
const double PARTICLE_BLOCK_WIDTH   = 10.0;
const double PARTICLE_BLOCK_HEIGHT  = 10.0;


//for a vol of 0.1 needs 5000 particles with 20 kernel particles

const int NUMBER_PARTICLES = 5000;
const int NUM_KERNEL_PARTICLES = 20;
const double VOLUMEN = 0.1;
const double DENSITY_WATER = 998.29;
const double MASS = 0.2;//DENSITY_WATER*VOLUMEN / NUMBER_PARTICLES;
const double H = .0624;//pow(3 * VOLUMEN*NUM_KERNEL_PARTICLES / 4 * PI*NUMBER_PARTICLES, 1.0 / 3);
const double PARTICLE_RADIUS = 0.1*pow(3 * MASS / 4 * PI*VOLUMEN, 1.0 / 3);
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

	/*Test*/
	Vec3 vel_p; //
	Vec3 a_p;

    double pressure;
    
    int index;//Numb. of the particle
    static int countParticles;//How many particles has been created
    static std::vector<Particle*> particles; //keep track of all created particles
    
	Particle(Vec3 position, Vec3 velocity);
	Vec3 getPosition(){ return position; };
	Vec3 getVelocity(){ return velocity; };
	void setPosition(Vec3 p){ position = p; };
    void setVelocity(Vec3 v){ velocity = v; };

	Vec3 getPreviousVelocity(){ return vel_p; };
	void setPreviousVelocity(Vec3 vp){ vel_p = vp; };
	Vec3 getPreviousAcceleration(){ return a_p; };
	void setPreviousAcceleration(Vec3 ap){ a_p = ap; };

    void setDensity(double d){ density = d; };
    void setPressure(double p){ pressure = p; };
	double getMass(){ return mass; };
	double getDensity(){ return density; };
	double getPressure(){ return pressure; };
	std::vector<Particle*> find_neighborhood(double  h);
	

};



	  


