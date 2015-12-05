#include "BasicLagrangian.h"

//Calculate density for each particle (at that position of that particle)
/*double calculateTotalDensity(Particle* particle) {
	double h = PARTICLE_RADIUS * 3; //1,0 radius aroun a given particle to look out for neighbours
	Vec3 r;
	std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
	double density = 0;

	for (int i = 0; i <listNeighbours.size(); i++)
	{
		r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
		density += listNeighbours[i]->getMass()*Poly6_kernel(r, H);
	}

	return density;
}*/

/*Calculate density in the position of the particle i*/

double calculateDensity(Particle* particle, std::vector<Particle*> particles) {
	double density = particle->getDensity();

	Vec3 r;

	for (unsigned i = 0; i < particles.size(); i++){
		r = difVec3(particle->getPosition(), particles[i]->getPosition());
		density += particles[i]->getMass()*Poly6_kernel(r, H);
	}
	return density;
}



// Calculate pressure for each particle(at that position of that particle)
double calculatePressure(Particle* particle) {
	return STIFFNESS_PARAMETER*(particle->getDensity() - REST_DENSITY);

}


//Calculate the gradient of the presuare at the pos of the particle i (symmetring the pressure force)
Vec3 calculateGradientPressure(Particle* particle, std::vector<Particle*> particles){
	Vec3 gradient;
	Vec3 r;
	double temp;
	
	for (unsigned i = 0; i < particles.size(); i++)
	{
		temp = 0;
		r = difVec3(particle->getPosition(), particles[i]->getPosition());
		//std::cout << "r.x: " << r.x << " r.y: " << r.y << " r.z: " << r.z << std::endl;
		temp = (particle->getPressure() / pow(particle->getDensity(), 2) + particles[i]->getPressure() / pow(particles[i]->getDensity(), 2))*
			particles[i]->getMass();
		//std::cout << temp << std::endl;
		gradient.x += temp*spiky_kernel_gradient(r, H).x;
		gradient.y += temp*spiky_kernel_gradient(r, H).y;
		gradient.z += temp*spiky_kernel_gradient(r, H).z;
		

	}

	gradient.x *= -particle->getDensity();
	gradient.y *= -particle->getDensity();
	gradient.z *= -particle->getDensity();

	return gradient;
}



//Calculate the viscosity force at the position of the particle i
Vec3 calculateViscosity(Particle* particle, std::vector<Particle*> particles){
		Vec3 viscosity;
		Vec3 r;
		Vec3 vel;
		double temp;

		for (unsigned i = 0; i < particles.size(); i++)
		{
			r = difVec3(particle->getPosition(), particles[i]->getPosition());
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

	//Calculate gravity force
	Vec3 calculateGravityForce(Particle* particle){
		Vec3 temp;
		temp.x = temp.z = 0;
		temp.y = particle->getDensity()*GRAVITY_COEFFICIENT;
		return temp;
	}

	//Calculate surface normal
	Vec3 calculateSurfaceNormal(Particle* particle){
		Vec3 normal;
		double temp;
		std::vector<Particle*> particles = particle->find_neighborhood(H);
		Vec3 r;
		for (unsigned i = 0; i < particles.size(); i++)
		{
			r = difVec3(particle->getPosition(), particles[i]->getPosition());
			temp = particles[i]->getMass() / particles[i]->getDensity();
			normal.x += temp*Poly6_kernel_gradient(r, H).x;
			normal.y += temp*Poly6_kernel_gradient(r, H).y;
			normal.z += temp*Poly6_kernel_gradient(r, H).z;
			
		}
		return normal;
	}

	//Calculate tension force
	Vec3 calculateTensionForce(Particle* particle){
		Vec3 force;
		double temp=0;
		std::vector<Particle*> particles = particle->find_neighborhood(H);
		Vec3 r;
		for (unsigned i = 0; i < particles.size(); i++)
		{
			r = difVec3(particle->getPosition(), particles[i]->getPosition());
			temp += (particles[i]->getMass() / particles[i]->getDensity())*Poly6_kernel_laplacian(r,H);
		}
		Vec3 normal = calculateSurfaceNormal(particle);

		force.x = -SIGMA*temp*normal.x / normVec3(normal);
		force.y = -SIGMA*temp*normal.y / normVec3(normal);
		force.z = -SIGMA*temp*normal.z / normVec3(normal);

		return force;
		
	}