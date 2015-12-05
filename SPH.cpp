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
	return initialState;
}

//ToDo check if this is correct!!  Calculates newPosition and newVelocity for all particles
void testRun(){
<<<<<<< HEAD
	std::vector<Particle*> particles = setInitialConditions();
	std::vector<Particle*> particlesList;
	for (unsigned i = 0; i < particles.size(); i++){
		particlesList = particles[i]->find_neighborhood(H);
		//cout << particlesList.size() << "\n\n";
		particles[i]->setDensity(calculateDensity(particles[i],particlesList));
		particles[i]->setPressure(calculatePressure(particles[i]));
=======
	//std::vector<Particle*> particles = setInitialConditions();

    for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		Particle::particles[i]->setDensity(calculateDensity(Particle::particles[i],particlesList));
		Particle::particles[i]->setPressure(calculatePressure(Particle::particles[i]));
>>>>>>> bc72a72ee32b330bec24fd1c91d143ecd1463979
		
	}

    //cout << "dens: " << Particle::particles[Particle::particles.size() - 1]->getDensity() << endl;
    //cout << "pres: " << Particle::particles[Particle::particles.size() - 1]->getPressure() << endl;
	
    //Calculate internal forces
	std::vector<Vec3> internalForce;
	std::vector<Vec3> forceP;

<<<<<<< HEAD
	for (unsigned i = 0; i < particles.size(); i++){
		particlesList = particles[i]->find_neighborhood(H);
		forceP.push_back(calculateGradientPressure(particles[i], particlesList));
		internalForce.push_back(sumVec3(calculateGradientPressure(particles[i], particlesList),
			calculateViscosity(particles[i], particlesList)));
		//cout << "f.x: " << forceP[i].x << " f.y: " << forceP[i].y << " f.z: " << forceP[i].z << endl;
=======
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		std::vector<Particle*> particlesList = Particle::particles[i]->find_neighborhood(H);
		internalForce.push_back(sumVec3(calculateGradientPressure(Particle::particles[i], particlesList),calculateViscosity(Particle::particles[i], particlesList)));
>>>>>>> bc72a72ee32b330bec24fd1c91d143ecd1463979
	}


	std::vector<Vec3> gravityForce;
	std::vector<Vec3> totalForce;
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		gravityForce.push_back(calculateGravityForce(Particle::particles[i]));
		//normal.push_back(calculateSurfaceNormal(particles[i]));	
		totalForce.push_back(sumVec3(internalForce[i],gravityForce[i]));
	}
	
	//Calculate acceleration
	std::vector<Vec3> acceleration;
<<<<<<< HEAD
	Vec3 temp;
	for (unsigned i = 0; i < particles.size(); i++){
		temp = Vec3(totalForce[i].x / particles[i]->getDensity(), totalForce[i].y / particles[i]->getDensity(), totalForce[i].z / particles[i]->getDensity());
		acceleration.push_back(temp);
		//cout << "a.x: " << acceleration[i].x << " a.y: " << acceleration[i].y << " a.z: " << acceleration[i].z << endl;
=======
	for (unsigned i = 0; i < Particle::particles.size(); i++){
		acceleration.push_back(multscalarVec3(totalForce[i], 1.0 / Particle::particles[i]->getDensity()));
>>>>>>> bc72a72ee32b330bec24fd1c91d143ecd1463979
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
<<<<<<< HEAD
	for (unsigned i = 0; i < particles.size(); i++){
		/*std::cout << "Position: " << particles[i]->getPosition().x << " " << particles[i]->getPosition().y << " "
			<< particles[i]->getPosition().z << "\nVelocity: " << particles[i]->getVelocity().x << " "
			<< particles[i]->getVelocity().y << " " << particles[i]->getVelocity().z << "\nDensity: "
			<< particles[i]->getDensity() << "\nPressure: " << particles[i]->getPressure() << "\n\n";*/
		particles[i]->setPosition(newPos[i]);
		particles[i]->setVelocity(newVel[i]);
=======
	for (unsigned i = 0; i < Particle::particles.size(); i++){
        //std::cout << "Position: " << Particle::particles[i]->getPosition().x << " " << Particle::particles[i]->getPosition().y << " " << Particle::particles[i]->getPosition().z << endl;
		//	<< " Velocity: " << particles[i]->getVelocity().x << " " << particles[i]->getVelocity().y << " " << particles[i]->getVelocity().z << std::endl;
        //newVel[i].x *= 10.0f;
        //newVel[i].y *= 10.0f;
        //newVel[i].z *= 10.0f;
		Particle::particles[i]->setPosition(newPos[i]);
		Particle::particles[i]->setVelocity(newVel[i]);
>>>>>>> bc72a72ee32b330bec24fd1c91d143ecd1463979
	}

    for (unsigned i = 0; i < Particle::particles.size(); i++){
        collision_info ci = detect_boundary_collision(Particle::particles[i]);
        //cout << "ci: " << ci.d << " " << ci.n.x << " " << ci.n.y << " " << ci.n.z << " " << ci.cp.x << " " <<ci.cp.y << " " <<ci.cp.z << endl;
        handle_collision(Particle::particles[i], ci, delta_t);
    }
}