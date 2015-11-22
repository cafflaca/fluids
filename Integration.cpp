#include "Integration.h"


Vec3 nextVelocity(Particle* particle, Vec3 force, double delta_t){
	Vec3 finalVel;
	finalVel.x = particle->getVelocity().x + delta_t*(force.x / particle->getMass());
	finalVel.y = particle->getVelocity().y + delta_t*(force.y / particle->getMass());
	finalVel.z = particle->getVelocity().z + delta_t*(force.z / particle->getMass());

	return finalVel;
}

Vec3 nextStep(Particle*particle, Vec3 velocity, double delta_t){
	Vec3 nextPos;
	nextPos.x = particle->getPosition().x + delta_t*(velocity.x);
	nextPos.y = particle->getPosition().y + delta_t*(velocity.y);
	nextPos.z = particle->getPosition().z + delta_t*(velocity.z);

	return nextPos;
}