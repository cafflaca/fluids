#pragma once

#include "SimpleMath.h"
#include "Particle.h"

Vec3 nextVelocity(Particle* particle, Vec3 force, double delta_t);

Vec3 nextStep(Particle*particle,Vec3 finalVel, double delta_t);