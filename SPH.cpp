#include "SPH.h"

std::vector<Particle*> setInitialConditions(){
	std::vector<Particle*> initialState;
	return initialState;
}

void testRun(){
	std::vector<Particle*> particles = setInitialConditions();

	std::vector<double> newPressure;
	std::vector<double> newDensity;
	//Calculate pressure and density
	for (unsigned i = 0; i < particles.size(); i++){
		newDensity.push_back(calculateDensity(particles[i]));
		newPressure.push_back(calculatePressure(particles[i]));	
	}
	
	for (unsigned i = 0; i < particles.size(); i++){
		particles[i]->setDensity(newDensity[i]);
		particles[i]->setPressure(newPressure[i]);
	}

	//Calculate internal forces
	std::vector<Vec3> internalForce;

	for (unsigned i = 0; i < particles.size(); i++){
		internalForce.push_back(sumVec3(calculateGradientPressure(particles[i]),
			calculateViscosity(particles[i])));
	}

}