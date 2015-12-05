#pragma once
#include "SimpleMath.h"
#include "Particle.h"
#include "Kernel.h"



const double REST_DENSITY = 998.29;//water
const double STIFFNESS_PARAMETER = 3;//NUMBER_PARTICLES*MASS*8.3144*293.15;
const double GRAVITY_COEFFICIENT = -9.819;
const double VISCOUSITY_COEFFICIENT = 3.5;//0.00351?
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