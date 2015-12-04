#include "SPH.h"
#include "Integration.h"

using namespace std;

std::vector<Particle*> setInitialConditions(){
	std::vector<Particle*> initialState;

	Vec3 initialVelocity = Vec3(0, 0, 0);

	for (int k = 0; k < PARTICLE_BLOCK_HEIGHT; k++) {
		for (int j = 0; j < PARTICLE_BLOCK_WIDTH; j++) {
			for (int i = 0; i < PARTICLE_BLOCK_LENGTH; i++) {
				initialState.push_back(new Particle(
					Vec3(
					(double)((double)i * PARTICLE_RADIUS * 2.0),
					(double)j * PARTICLE_RADIUS * 2.0,
					(double)k * PARTICLE_RADIUS * 2.0
					),
					initialVelocity));
			}
		}
	}
	return initialState;
}

//ToDo check if this is correct!!  Calculates newPosition and newVelocity for all particles
void testRun(){
	std::vector<Particle*> particles = setInitialConditions();

	std::vector<double> newPressure;
	std::vector<double> newDensity;
	//Calculate pressure and density
	
	for (unsigned i = 0; i < particles.size(); i++){
		std::vector<Particle*> particlesList = particles[i]->find_neighborhood(H);
		particles[i]->setDensity(calculateDensity(particles[i],particlesList));
		cout << "Final "<<particles[i]->getDensity()<<", ";
		cout << particles[i]->getPressure() << endl;
		particles[i]->setPressure(calculatePressure(particles[i]));
	}


	//Calculate internal forces
	std::vector<Vec3> internalForce;

	for (unsigned i = 0; i < particles.size(); i++){
		std::vector<Particle*> particlesList = particles[i]->find_neighborhood(H);
		internalForce.push_back(sumVec3(calculateGradientPressure(particles[i], particlesList),
			calculateViscosity(particles[i], particlesList)));
	}

	//Calculate acceleration
	std::vector<Vec3> acceleration;
	for (unsigned i = 0; i < particles.size(); i++){
		acceleration.push_back(multscalarVec3(internalForce[i], 1.0 / particles[i]->getDensity()));
	}

	//Calculate new position and velocity
	std::vector<Vec3> newPos;
	std::vector<Vec3> newVel;
	double delta_t = 0.1;
	for (unsigned i = 0; i < particles.size(); i++){
		newVel.push_back(nextVelocity(particles[i], acceleration[i], delta_t));
		newPos.push_back(nextStep(particles[i], newVel[i], delta_t));
	}

	//Update position and velocity
	for (unsigned i = 0; i < particles.size(); i++){
		particles[i]->setPosition(newPos[i]);
		particles[i]->setVelocity(newVel[i]);
	}

}