#include "BasicLagrangian.h"


/*Calculate density in the position of the particle i*/

double calculateDensity(Particle* particle) {
	std::vector<Particle*> particlesN = particle->getAdjList();
    double density = particle->getDensity(); //0;//
	
	Vec3 r;

	for (unsigned i = 0; i < particlesN.size(); i++){
		r = difVec3(particle->getPosition(), particlesN[i]->getPosition());
		density += particlesN[i]->getMass()*Poly6_kernel(r, H);
	}
	return density;
}



// Calculate pressure for each particle(at that position of that particle)
double calculatePressure(Particle* particle) {
	return STIFFNESS_PARAMETER*(particle->getDensity() - REST_DENSITY);

}


//Calculate the gradient of the presuare at the pos of the particle i (symmetring the pressure force)
Vec3 calculateGradientPressure(Particle* particle){
	std::vector<Particle*> particlesN = particle->getAdjList();
	Vec3 gradient;
	Vec3 r;
	double temp=0;
	
	for (unsigned i = 0; i < particlesN.size(); i++)
	{
		//temp = 0;
		r = difVec3(particle->getPosition(), particlesN[i]->getPosition());
		//std::cout << "r.x: " << r.x << " r.y: " << r.y << " r.z: " << r.z << std::endl;
		temp = ((particle->getPressure() / pow(particle->getDensity(), 2)) + (particlesN[i]->getPressure() / pow(particlesN[i]->getDensity(), 2)))
			*particlesN[i]->getMass();
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
Vec3 calculateViscosity(Particle* particle){
	std::vector<Particle*> particlesN = particle->getAdjList();
	Vec3 viscosity;
		Vec3 r;
		Vec3 vel;
		double temp=0;

		for (unsigned i = 0; i < particlesN.size(); i++)
		{
			r = difVec3(particle->getPosition(), particlesN[i]->getPosition());
			temp = (particlesN[i]->getMass() / particlesN[i]->getDensity())*viscosity_laplacian_kernel(r, H);
			vel = difVec3(particlesN[i]->getVelocity(), particle->getVelocity());
			viscosity.x += vel.x*temp;
			viscosity.y += vel.y*temp;
			viscosity.z += vel.z*temp;
		}

		viscosity.x *= VISCOUSITY_COEFFICIENT ;
		viscosity.y *= VISCOUSITY_COEFFICIENT ;
		viscosity.z *= VISCOUSITY_COEFFICIENT ;

		return viscosity;
	}

	//Calculate gravity force
	Vec3 calculateGravityForce(Particle* particle){
		Vec3 temp;
		temp.x = particle->getDensity()*GRAVITY_COEFFICIENT.x;
		temp.y = particle->getDensity()*GRAVITY_COEFFICIENT.y;
		temp.z = particle->getDensity()*GRAVITY_COEFFICIENT.z;
		return temp;
	}

	//Calculate surface normal
	Vec3 calculateSurfaceNormal(Particle* particle){
		std::vector<Particle*> particlesN = particle->getAdjList();
		Vec3 normal;
		double temp=0;
		Vec3 r;
		for (unsigned i = 0; i < particlesN.size(); i++)
		{
			r = difVec3(particle->getPosition(), particlesN[i]->getPosition());
			temp = particlesN[i]->getMass() / particlesN[i]->getDensity();
			normal.x += temp*Poly6_kernel_gradient(r, H).x;
			normal.y += temp*Poly6_kernel_gradient(r, H).y;
			normal.z += temp*Poly6_kernel_gradient(r, H).z;
			
		}
		return normal;
	}

	//Calculate tension force
	Vec3 calculateTensionForce(Particle* particle, Vec3 normal){
		std::vector<Particle*> particlesN = particle->getAdjList();
		Vec3 force;
		double temp=0;
		Vec3 r;
		for (unsigned i = 0; i < particlesN.size(); i++)
		{
			r = difVec3(particle->getPosition(), particlesN[i]->getPosition());
			temp += (particlesN[i]->getMass() / particlesN[i]->getDensity())*Poly6_kernel_laplacian(r, H);
		}
		

		force.x = -SURFACE_TENSION*temp*normal.x / normVec3(normal);
		force.y = -SURFACE_TENSION*temp*normal.y / normVec3(normal);
		force.z = -SURFACE_TENSION*temp*normal.z / normVec3(normal);

		return force;
		
	}