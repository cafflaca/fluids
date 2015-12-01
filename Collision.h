#pragma once

#include <stdio.h>
#include "Particle.h"
#include "SimpleMath.h"

struct collision_info{
    bool collided;
    Vec3 cp;        // Contact point
    Vec3 n;         // Surface normal at the contact point
    double d;       // Penetration depth
};

collision_info detect_particle_collision(Particle* particle);

collision_info detect_boundary_collision(Particle* particle);

void handle_collision(Particle* particle, collision_info ci, double timestep);