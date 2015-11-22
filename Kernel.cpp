#include "Kernel.h"

//Pos - Vector between two particles i and j -> rij , h is the compact support radius H

double Poly6_kernel(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance <= h &&  distance >= 0){
		kernel = 315.0 / (64.0 * PI *pow(h, 9)) * pow(h*h - pow(distance,2), 3);
	}
	return kernel;
}

double Poly6_kernel_gradient(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance >= 0 && distance <= h)
	{
		// Using the gradient of the poly6 smoothing kernel, see p.30
		kernel = -945.0 / (32.0 * PI * pow(h, 9)) * distance * pow(h*h - pow(distance, 2), 2);
	}
	return kernel;
}

double Poly6_kernel_laplacian(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance >= 0 && distance <= h)
	{
		// Using the gradient of the poly6 smoothing kernel, see p.30
		kernel = -945.0 / (32.0 * PI * pow(h, 9)) * (h*h - pow(distance, 2))*(3.0*h*h - 7.0*pow(distance, 2));
	}
	return kernel;
}
//To do: Check the rest of the kernels.

double spiky_kernel(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance >= 0 && distance <= h)
	{
		// Using poly6 smoothing kernel, see p.30
		kernel = (15.f / (PI * pow(h, 6))) *pow(h - distance, 3);
	}
	return kernel;
}

double spiky_kernel_gradient(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance >= 0 && distance <= h)
	{
		// Using poly6 smoothing kernel, see p.30
		kernel = (45.f / (PI * pow(h, 6))) / distance *pow(h - distance, 2);
	}
	
	return kernel;
}

double viscous_kernel(Vec3 pos, double h){
	double kernel = 0;
	double distance = normVec3(pos);
	if (distance >= 0 && distance <= h)
	{
		// Using poly6 smoothing kernel, see p.30
		kernel = (15 / (2 * PI * pow(h, 3))) *(-pow(distance, 3) / (2 * pow(h, 3)) + pow(distance, 2) / (pow(h, 2)) + h / (2 * distance) - 1);
	}
	
	return kernel;
}