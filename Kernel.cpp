#include "Kernel.h"

double applyKernelPoly6(Vec3 pos, double h){
	double kernel = 0;
	double normP = normVec3(pos);
	if (normP <= h &&  normP >= 0){
		kernel = (315.0 / (64.0*PI*pow(h, 9)))*pow((h*h - normP*normP), 3);
	}
	return kernel;
}