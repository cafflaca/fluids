#pragma once
#include "SimpleMath.h"
#include "Particle.h"
#include "Kernel.h"


const double H = pow(3 * VOLUMEN*NUM_KERNEL_PARTICLES / 4 * PI*NUMBER_PARTICLES, 1.0 / 3);
const double REST_DENSITY = 998.29;//water
const double STIFFNESS_PARAMETER = NUMBER_PARTICLES*MASS*8.3144*293.15;
const double GRAVITY_COEFFICIENT = -9.819;
const double VISCOUSITY_COEFFICIENT = 0.0091;//0.00351?
const double SIGMA = 0.0728;	


double calculateTotalDensity(Particle* particle);

double calculateDensity(Particle* particle, std::vector<Particle*> particles);

double calculatePressure(Particle* particle);

//double calculateLaplacianPressureA(Particle* particle);

Vec3 calculateGradientPressure(Particle* particle, std::vector<Particle*> particles);

Vec3 calculateViscosity(Particle* particle, std::vector<Particle*> particles);

Vec3 calculateGravityForce(Particle* particle);

Vec3 calculateSurfaceNormal(Particle* particle);

//Calculate tension force
Vec3 calculateTensionForce(Particle* particle);