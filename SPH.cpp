#include "SPH.h"
#include "Particle.h"

using namespace std;

std::vector<Particle*> setInitialConditions(){
	std::vector<Particle*> initialState;

	Vec3 initialVelocity = Vec3(0, 0, 0);

	for (int k = 0; k < PARTICLE_BLOCK_HEIGHT; k++) {
		for (int j = 0; j < PARTICLE_BLOCK_WIDTH; j++) {
			for (int i = 0; i < PARTICLE_BLOCK_LENGTH; i++) {
				initialState.push_back(new Particle(
					Vec3(
					i * PARTICLE_RADIUS * 2.0,
					j * PARTICLE_RADIUS * 2.0,
					k * PARTICLE_RADIUS * 2.0),
					initialVelocity));
			}
		}
	}
	return initialState;
}

//ToDo check if this is correct!!  Calculates newPosition and newVelocity for all particles
void testRun(){
	std::vector<Particle*> particles = setInitialConditions();
	std::vector<Particle*> particlesList;
	for (unsigned i = 0; i < particles.size(); i++){
		particlesList = particles[i]->find_neighborhood(H);
		//cout << particlesList.size() << "\n\n";
		particles[i]->setDensity(calculateDensity(particles[i],particlesList));
		particles[i]->setPressure(calculatePressure(particles[i]));
		
	}


	//Calculate internal forces
	std::vector<Vec3> internalForce;
	std::vector<Vec3> forceP;

	for (unsigned i = 0; i < particles.size(); i++){
		particlesList = particles[i]->find_neighborhood(H);
		forceP.push_back(calculateGradientPressure(particles[i], particlesList));
		internalForce.push_back(sumVec3(calculateGradientPressure(particles[i], particlesList),
			calculateViscosity(particles[i], particlesList)));
		//cout << "f.x: " << forceP[i].x << " f.y: " << forceP[i].y << " f.z: " << forceP[i].z << endl;
	}


	std::vector<Vec3> gravityForce;
	std::vector<Vec3> totalForce;
	for (unsigned i = 0; i < particles.size(); i++){
		gravityForce.push_back(calculateGravityForce(particles[i]));
		//normal.push_back(calculateSurfaceNormal(particles[i]));	
		totalForce.push_back(sumVec3(internalForce[i],gravityForce[i]));
	}
	
	//Calculate acceleration
	std::vector<Vec3> acceleration;
	Vec3 temp;
	for (unsigned i = 0; i < particles.size(); i++){
		temp = Vec3(totalForce[i].x / particles[i]->getDensity(), totalForce[i].y / particles[i]->getDensity(), totalForce[i].z / particles[i]->getDensity());
		acceleration.push_back(temp);
		//cout << "a.x: " << acceleration[i].x << " a.y: " << acceleration[i].y << " a.z: " << acceleration[i].z << endl;
	}

	//Calculate new position and velocity
	std::vector<Vec3> newPos;
	std::vector<Vec3> newVel;
	double delta_t = 0.5;
	for (unsigned i = 0; i < particles.size(); i++){
		newVel.push_back(nextVelocity(particles[i], acceleration[i], delta_t));
		newPos.push_back(nextStep(particles[i], newVel[i], delta_t));
	}

	//Update position and velocity
	for (unsigned i = 0; i < particles.size(); i++){
		/*std::cout << "Position: " << particles[i]->getPosition().x << " " << particles[i]->getPosition().y << " "
			<< particles[i]->getPosition().z << "\nVelocity: " << particles[i]->getVelocity().x << " "
			<< particles[i]->getVelocity().y << " " << particles[i]->getVelocity().z << "\nDensity: "
			<< particles[i]->getDensity() << "\nPressure: " << particles[i]->getPressure() << "\n\n";*/
		particles[i]->setPosition(newPos[i]);
		particles[i]->setVelocity(newVel[i]);
	}

}