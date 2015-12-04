#include "SPH.h"
#include "Particle.h"
#include "Collision.h"

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

	std::vector<double> newPressure;
	std::vector<double> newDensity;
	//Calculate pressure and density
    for (unsigned i = 0; i < Particle::particles.size(); i++){
		newDensity.push_back(calculateDensity(Particle::particles[i]));
		newPressure.push_back(calculatePressure(Particle::particles[i]));
	}
    
	//Update density and pressure
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		Particle::particles[i]->setDensity(newDensity[i]);
		Particle::particles[i]->setPressure(newPressure[i]);
	}
    //std::cout << "dens: " << newDensity[Particle::particles.size() - 1] << std::endl;
    //std::cout << "pres: " << newPressure[Particle::particles.size() - 1] << std::endl;
	//Calculate internal forces
	std::vector<Vec3> internalForce;

	for (unsigned i = 0; i < Particle::particles.size(); i++){
		internalForce.push_back(sumVec3(calculateGradientPressure(Particle::particles[i]),
			calculateViscosity(Particle::particles[i])));
	}
    
    //std::cout << "force: " << internalForce[Particle::particles.size() - 1].x << " "
    //<< internalForce[Particle::particles.size() - 1].y << " "
    //<< internalForce[Particle::particles.size() - 1].z << std::endl;;

	//Calculate acceleration
	std::vector<Vec3> acceleration;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		acceleration.push_back(multscalarVec3(internalForce[i], 1.0 / Particle::particles[i]->getDensity()));
	}
    //std::cout << "acc: " << acceleration[Particle::particles.size() - 1].x << " "
    //<< acceleration[Particle::particles.size() - 1].y << " "
    //<< acceleration[Particle::particles.size() - 1].z << std::endl;;
	//Calculate new position and velocity
	std::vector<Vec3> newPos;
	std::vector<Vec3> newVel;
	double delta_t = 0.01;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		newVel.push_back(nextVelocity(Particle::particles[i], acceleration[i], delta_t));
		newPos.push_back(nextStep(Particle::particles[i], newVel[i], delta_t));
	}

    std::cout << "v: " << newPos[Particle::particles.size() - 1].x << " "
    << newPos[Particle::particles.size() - 1].y << " "
    << newPos[Particle::particles.size() - 1].z << std::endl;;
	//Update position and velocity
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		Particle::particles[i]->setPosition(newPos[i]);
        newVel[i].x *= 10.f;
        newVel[i].y *= 10.f;
        newVel[i].z *= 10.f;
        Particle::particles[i]->setVelocity(newVel[i]);
	}
    
    /*for (unsigned i = 0; i < Particle::particles.size(); i++){

        collision_info ci = detect_boundary_collision(Particle::particles[i]);
        handle_collision(Particle::particles[i], ci, delta_t);
        //Particle::particles[i]->setPosition(newPos[i]);
        //Particle::particles[i]->setVelocity(newVel[i]);
    }*/

}