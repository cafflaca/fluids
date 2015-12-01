#pragma once
#include "SimpleMath.h"
#include "Particle.h"

const double H = pow(3 * VOLUMEN*NUM_KERNEL_PARTICLES / 4 * PI*NUMBER_PARTICLES, 1.0 / 3);
const double REST_DENSITY = 998.29;//water
const double STIFFNESS_PARAMETER = 1000;
const double GRAVITY_COEFFICIENT = 9.819;
const double VISCOUSITY_COEFFICIENT = 0.0091;


double calculateTotalDensity(Particle* particle);

double calculateDensity(Particle* particle);

double calculatePressure(Particle* particle);

//double calculateLaplacianPressureA(Particle* particle);

Vec3 calculateGradientPressure(Particle* particle);

Vec3 calculateViscosity(Particle* particle);

double calculateGravityForce(Particle* particle);