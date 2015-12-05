

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
					i * PARTICLE_RADIUS * 2.0,
					j * PARTICLE_RADIUS * 2.0,
					k * PARTICLE_RADIUS * 2.0),
					initialVelocity));

			}
		}
	}
	/*Test*/
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		Particle::particles[i]->vel_p = Particle::particles[i]->velocity;
		Particle::particles[i]->a_p = Vec3(0, 0, 0);
	}
	return initialState;
}

//ToDo check if this is correct!!  Calculates newPosition and newVelocity for all particles
void testRun(double t){
	//std::vector<Particle*> particles = setInitialConditions();

	for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		Particle::particles[i]->setDensity(calculateDensity(Particle::particles[i], particlesList));
		Particle::particles[i]->setPressure(calculatePressure(Particle::particles[i]));

	}


	//Calculate internal forces
	std::vector<Vec3> internalForce;

	for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		internalForce.push_back(sumVec3(calculateGradientPressure(Particle::particles[i], particlesList), calculateViscosity(Particle::particles[i], particlesList)));
	}
    
    //cout << "force: " << internalForce[Particle::particles.size() - 1].x << " "<< internalForce[Particle::particles.size() - 1].y << " "<< internalForce[Particle::particles.size() - 1].z << endl;;

	//Calculate external forces
	//std::vector<Vec3> externalForce;
	std::vector<Vec3> gravityForce;
	//std::vector<Vec3> normal;
	//std::vector<Vec3> surfaceForce;
	std::vector<Vec3> totalForce;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		gravityForce.push_back(calculateGravityForce(Particle::particles[i]));
		//normal.push_back(calculateSurfaceNormal(particles[i]));	
		totalForce.push_back(sumVec3(internalForce[i], gravityForce[i]));
	}

	//Calculate acceleration
	std::vector<Vec3> acceleration;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		acceleration.push_back(multscalarVec3(totalForce[i], 1.0 / Particle::particles[i]->getDensity()));
	}
    cout << "acc: " << acceleration[1].x << " " << acceleration[1].y << " " << acceleration[1].z << " " << endl;
	//Calculate new position and velocity
	std::vector<Vec3> newPos;
	std::vector<Vec3> newVel;
	double delta_t = 0.01;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		//newVel.push_back(nextVelocity(Particle::particles[i], acceleration[i], delta_t));
		//newPos.push_back(nextStep(Particle::particles[i], newVel[i], delta_t));

		/*Test*/

		newVel.push_back(leapFrog_vel(Particle::particles[i], acceleration[i], Particle::particles[i]->a_p, Particle::particles[i]->vel_p, delta_t));
		newPos.push_back(nextStep(Particle::particles[i], newVel[i], delta_t));
	}

	//Update position and velocity
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		/*Test*/
		Particle::particles[i]->setPosition(newPos[i]);

		Vec3 vel_half;
		vel_half.x = Particle::particles[i]->vel_p.x - 0.5*delta_t*Particle::particles[i]->a_p.x;
		vel_half.y = Particle::particles[i]->vel_p.y - 0.5*delta_t*Particle::particles[i]->a_p.y;
		vel_half.z = Particle::particles[i]->vel_p.z - 0.5*delta_t*Particle::particles[i]->a_p.z;
		Vec3 next_vel;
		next_vel.x = (vel_half.x + newVel[i].x) / 2.0;
		next_vel.y = (vel_half.y + newVel[i].y) / 2.0;
		next_vel.z = (vel_half.z + newVel[i].z) / 2.0;

		Particle::particles[i]->setPreviousVelocity(Particle::particles[i]->velocity);
		Particle::particles[i]->setVelocity(next_vel);

		/*Particle::particles[i]->setPosition(newPos[i]);
		Particle::particles[i]->setVelocity(newVel[i]);*/
	}

	for (unsigned i = 0; i < Particle::particles.size(); i++){
		collision_info ci = detect_boundary_collision(Particle::particles[i]);
        handle_collision(Particle::particles[i], ci, delta_t);
        //collision_info ci_p = detect_particle_collision(Particle::particles[i]);
        //handle_collision(Particle::particles[i], ci_p, delta_t);

        
	}
}



