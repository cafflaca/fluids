#include "Integration.h"


Vec3 nextVelocity(Particle* particle, Vec3 acceleration, double delta_t){
	Vec3 finalVel;
	finalVel.x = particle->getVelocity().x + delta_t*acceleration.x;
	finalVel.y = particle->getVelocity().y + delta_t*acceleration.y;
	finalVel.z = particle->getVelocity().z + delta_t*acceleration.z;

	return finalVel;
}

Vec3 nextStep(Particle*particle, Vec3 velocity, double delta_t){
	Vec3 nextPos;
	nextPos.x = particle->getPosition().x + delta_t*(velocity.x);
	nextPos.y = particle->getPosition().y + delta_t*(velocity.y);
	nextPos.z = particle->getPosition().z + delta_t*(velocity.z);
	return nextPos;
}

Vec3 leapFrog_vel(Particle* particle, Vec3 a, Vec3 a_p, Vec3 p_vel, double delta_t){
	Vec3 vel_half;
	vel_half.x = p_vel.x - 0.5*delta_t*a_p.x;
	vel_half.y = p_vel.y - 0.5*delta_t*a_p.y;
	vel_half.z = p_vel.z - 0.5*delta_t*a_p.z;

	Vec3 vel_final;
	vel_final.x = vel_half.x + delta_t*a.x;
	vel_final.y = vel_half.y + delta_t*a.y;
	vel_final.z = vel_half.z + delta_t*a.z;

	return vel_final;

}




