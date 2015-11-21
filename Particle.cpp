#include "Particle.h"

int Particle::countParticles = 0;
std::vector<Particle> Particle::particles;

Particle::Particle(Vec3 position, Vec3 velocity, Vec3 acceleration){
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	
	label = countParticles; // 0 to totalNumb -1
	countParticles++;
	particles.push_back(this);
}

std::vector<Particle>Particle::find_neighborhood(double  h){
	double distance = 0;
	std::vector<Particle> list;

	for (unsigned i = 0; i < countParticles; i++){
		if (i != label){
			distance = distanceVec3(position, particles[i].getPosition());
			if (distance <= h)
				list.push_back(particles[i]);
		}
	}
	return list;
}


double Particle::applyKernelPoly6(Vec3 pos, double h){
	double kernel = 0;
	double normP = normVec3(pos);
	if (normP <= h &&  normP >= 0){
		kernel = (315.0 / (64.0*PI*pow(h, 9)))*pow((h*h - normP*normP), 3);
	}
	return kernel;
}