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

void Particle::find_neighborhood(double  h){
	double distance;
	adjList.clear();
	for (int i = 0; i < particles.size(); i++){
		if (i != index){
			distance = 0;
			distance = distanceVec3(position, particles[i]->getPosition());
			if (distance <= h){
				adjList.push_back(particles[i]);
			}
		}

	}

	/*std::cout << " Number of neighbors: " << this->adjList.size() << std::endl;
	std::cout << "Sample size: " << countParticles << " or " << particles.size() << std::endl;*/

}
 