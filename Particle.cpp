#include "Particle.h"

int Particle::countParticles = 0;
std::vector<Particle*> Particle::particles;

Particle::Particle(Vec3 position, Vec3 velocity){
	this->position = position;
	this->velocity = velocity;
	density = DENSITY_WATER;
	pressure = 101325;
	mass = MASS; 
	
	index = countParticles; // 0 to totalNumb -1
	countParticles++;
	particles.push_back(this);
}


std::vector<Particle*>Particle::find_neighborhood(double  h){
	double distance = 0;
	std::vector<Particle*> list;

	for (int i = 0; i < countParticles; i++){
		if (i != index){
			distance = distanceVec3(position, particles[i]->getPosition());
			if (distance <= h){
				list.push_back(particles[i]);
			}
		}
	}
	return list;
}
 