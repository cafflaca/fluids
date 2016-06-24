#pragma once
#include "SimpleMath.h"
#include "Particle.h"
#include "Kernel.h"



const double REST_DENSITY = 998.29;//water
const double STIFFNESS_PARAMETER = 3;//NUMBER_PARTICLES*MASS*8.3144*293.15;//3
const Vec3 GRAVITY_COEFFICIENT = Vec3(0, -9.819,0 );
const double VISCOUSITY_COEFFICIENT = 3.5;//0.00351?
const double SURFACE_TENSION = 0.0728;
const double SURFACE_THRESHOLD = 7.065;
const double SIGMA = 0.0728;	

double calculateDensity(Particle* particle);

double calculatePressure(Particle* particle);

//double calculateLaplacianPressureA(Particle* particle);

Vec3 calculateGradientPressure(Particle* particle);

Vec3 calculateViscosity(Particle* particle);

Vec3 calculateGravityForce(Particle* particle);

Vec3 calculateSurfaceNormal(Particle* particle);

//Calculate tension force
Vec3 calculateTensionForce(Particle* particle, Vec3 normal);