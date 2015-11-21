#pragma once
#include "SimpleMath.h"

double Poly6_kernel(Vec3 pos, double h);

//double Poly6_kernel_gradient(Vec3 pos, double h);

double spiky_kernel(Vec3 pos, double h);

double spiky_kernel_gradient(Vec3 pos, double h);

double viscous_kernel(Vec3 pos, double h);