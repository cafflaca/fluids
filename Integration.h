#pragma once

#include "SimpleMath.h"
#include "Particle.h"


Vec3 nextVelocity(Particle* particle, Vec3 acceleration, double delta_t);

Vec3 nextStep(Particle*particle,Vec3 finalVel, double delta_t);

Vec3 leapFrog_vel(Particle* particle, Vec3 a, Vec3 p_a, Vec3 p_vel, double delta_t);

