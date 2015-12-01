#include "BasicLagrangian.h"
#include "kernel.h"

//Calculate density for each particle (at that position of that particle)
double calculateTotalDensity(Particle* particle) {
	double h = 1.0; // radius aroun a given particle to look out for neighbours
	Vec3 r;
	std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
	double density = 0;

	for (int i = 0; i <listNeighbours.size(); i++)
	{
		r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
		density += listNeighbours[i]->getMass()*Poly6_kernel(r, H);
	}

	return density;
}

/*Calculate density in the position of the particle i*/
double calculateDensity(Particle* particle) {
	double density = 0;
	std::vector<Particle*> particles = particle->getParticleSample();
	Vec3 r;

	for (unsigned i = 0; i < particles.size();i++){
	    r = difVec3(particle->getPosition(), particles[i]->getPosition());
		density += particles[i]->getMass()*Poly6_kernel(r,H);
	}
	return density;	
}

// Calculate pressure for each particle(at that position of that particle)
double calculatePressure(Particle* particle) {
	return STIFFNESS_PARAMETER*(particle->getDensity() - REST_DENSITY);
}

/*double calculateLaplacianPressureA(Particle* particle){
	double laplacian = 0;
	Vec3 r;
	double h = 1.0;
	std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
	// See p.33
	for (unsigned i = 0; i < listNeighbours.size(); i++)
	{
		r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
		laplacian += (1.0 / listNeighbours[i]->getDensity()) * listNeighbours[i]->getPressure() * Poly6_kernel_gradient(r, h);

	}

	laplacian *= particle->getMass();

	return laplacian;
}*/

//Calculate the gradient of the presuare at the pos of the particle i (symmetring the pressure force)
Vec3 calculateGradientPressure(Particle* particle){
	Vec3 gradient;
	Vec3 r;
	double temp;

	std::vector<Particle*> particles = particle->getParticleSample();
	
	for (unsigned i = 0; i < particles.size(); i++)
	{
		temp = 0;
		r = difVec3(particle->getPosition(), particles[i]->getPosition());
		temp = (particle->getPressure() / pow(particle->getDensity(), 2) + particles[i]->getPressure() / pow(particles[i]->getDensity(), 2))*
			particles[i]->getMass();
		gradient.x += temp*spiky_kernel_gradient(r, H).x;
		gradient.y += temp*spiky_kernel_gradient(r, H).y;
		gradient.z += temp*spiky_kernel_gradient(r, H).z;

	}

	gradient.x *= -particle->getMass();
	gradient.y *= -particle->getMass();
	gradient.z *= -particle->getMass();

	return gradient;
}

	/*void compute_force_density(Particle* particle){
		Vec3 mF;
		double mFp; // You have to initialize please, I dont know if you initialize this variable.
		double h = 1.0; // radius aroun a given particle to look out for neighbours
		Vec3 r;
		std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
		double weight;
		//float mFx = 0, mFy = 0, mFz = 0;
		for (int i = 0; i < listNeighbours.size(); i++)
		{
			r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
			
			//presure part: - gradient p
			weight = spiky_kernel_gradient(r,h);
			mFp = -particle->getMass() / listNeighbours[i]->getDensity()*(particle->getPressure() - listNeighbours[i]->getPressure())*weight;
			mF.x += mFp*r.x;
			mF.y += mFp*r.y;
			mF.z += mFp*r.z;

			//viscocity part: nu laplacia u
			weight = viscous_kernel(r,h);
			mF.x += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().x - particle->getVelocity().x) / listNeighbours[i]->getDensity()*weight;
			mF.y += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().y - particle->getVelocity().y) / listNeighbours[i]->getDensity()*weight;
			mF.z += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().z - particle->getVelocity().z) / listNeighbours[i]->getDensity()*weight;
		}
		//gravity part: g
		mF.y += particle->getDensity()*GRAVITY_COEFFICIENT*-1;

		// force density
		Vec3 force;
		force.x = mF.x;
		force.y = mF.y;
		force.z = mF.z;
	}*/

//Calculate the viscosity force at the position of the particle i
	Vec3 calculateViscosity(Particle* particle){
		Vec3 viscosity;
		Vec3 r;
		Vec3 vel;
		double temp;
		std::vector<Particle*> particles = particle->getParticleSample();

		for (unsigned i = 0; i < particles.size(); i++)
		{
			temp = particles[i]->getMass()*viscosity_laplacian_kernel(r,H);
			vel = difVec3(particles[i]->getVelocity(), particle->getVelocity());
			viscosity.x += vel.x*temp;
			viscosity.y += vel.y*temp;
			viscosity.z += vel.z*temp;
		}

		viscosity.x *= VISCOUSITY_COEFFICIENT / particle->getDensity();
		viscosity.y *= VISCOUSITY_COEFFICIENT / particle->getDensity();
		viscosity.z *= VISCOUSITY_COEFFICIENT / particle->getDensity();

		return viscosity;
	}

	double calculateGravityForce(Particle* particle){
		return particle->getDensity()*GRAVITY_COEFFICIENT;
	}