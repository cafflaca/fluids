#include "SPH.h"
#include "Particle.h"
#include "Collision.h"

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
	//std::vector<Particle*> particles = setInitialConditions();

    for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		Particle::particles[i]->setDensity(calculateDensity(Particle::particles[i],particlesList));
		Particle::particles[i]->setPressure(calculatePressure(Particle::particles[i]));
		
	}

    //cout << "dens: " << Particle::particles[Particle::particles.size() - 1]->getDensity() << endl;
    //cout << "pres: " << Particle::particles[Particle::particles.size() - 1]->getPressure() << endl;
	
    //Calculate internal forces
	std::vector<Vec3> internalForce;

	for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		internalForce.push_back(sumVec3(calculateGradientPressure(Particle::particles[i], particlesList),calculateViscosity(Particle::particles[i], particlesList)));
	}

	//Calculate external forces
	//std::vector<Vec3> externalForce;
	std::vector<Vec3> gravityForce;
	//std::vector<Vec3> normal;
	//std::vector<Vec3> surfaceForce;
	std::vector<Vec3> totalForce;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		gravityForce.push_back(calculateGravityForce(Particle::particles[i]));
		//normal.push_back(calculateSurfaceNormal(particles[i]));	
		totalForce.push_back(sumVec3(internalForce[i],gravityForce[i]));
	}
	
	//Calculate acceleration
	std::vector<Vec3> acceleration;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		acceleration.push_back(multscalarVec3(totalForce[i], 1.0 / Particle::particles[i]->getDensity()));
	}

	//Calculate new position and velocity
	std::vector<Vec3> newPos;
	std::vector<Vec3> newVel;
	double delta_t = 0.1;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		newVel.push_back(nextVelocity(Particle::particles[i], acceleration[i], delta_t));
		newPos.push_back(nextStep(Particle::particles[i], newVel[i], delta_t));
	}

	//Update position and velocity
	for (unsigned i = 0; i < Particle::particles.size(); i++){
        //std::cout << "Position: " << Particle::particles[i]->getPosition().x << " " << Particle::particles[i]->getPosition().y << " " << Particle::particles[i]->getPosition().z << endl;
		//	<< " Velocity: " << particles[i]->getVelocity().x << " " << particles[i]->getVelocity().y << " " << particles[i]->getVelocity().z << std::endl;
        //newVel[i].x *= 10.0f;
        //newVel[i].y *= 10.0f;
        //newVel[i].z *= 10.0f;
		Particle::particles[i]->setPosition(newPos[i]);
		Particle::particles[i]->setVelocity(newVel[i]);
	}

    for (unsigned i = 0; i < Particle::particles.size(); i++){
        collision_info ci = detect_boundary_collision(Particle::particles[i]);
        //cout << "ci: " << ci.d << " " << ci.n.x << " " << ci.n.y << " " << ci.n.z << " " << ci.cp.x << " " <<ci.cp.y << " " <<ci.cp.z << endl;
        handle_collision(Particle::particles[i], ci, delta_t);
    }
}