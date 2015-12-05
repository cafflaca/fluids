#pragma once
#include "SimpleMath.h"

double Poly6_kernel(Vec3 pos, double h);

Vec3 Poly6_kernel_gradient(Vec3 pos, double h);

double Poly6_kernel_laplacian(Vec3 pos, double h);

double spiky_kernel(Vec3 pos, double h);

Vec3 spiky_kernel_gradient(Vec3 r, double h);

double viscosity_kernel(Vec3 pos, double h);

double viscosity_laplacian_kernel(Vec3 pos, double h);