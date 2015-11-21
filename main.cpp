#include <iostream>
#include <math.h>
#include "Particle.h"
#include "Kernel.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include "GL/glut.h"
#else
#include <GL/freeglut.h>
#endif
#endif

using namespace std; 

const double REST_DENSITY = 1000;
const double STIFFNESS_PARAMETER = 1000;

//TODO: Ning's gravity coefficient and viscousity coefficient
const float GRAVITY_COEFFICIENT = 9.8;
const float VISCOUSITY_COEFFICIENT = 0.0091;

//Calculate density for each particle (at that position of that particle)
double calculateDensity(Particle* particle) {
	double h = 1.0; // radius aroun a given particle to look out for neighbours
	Vec3 r;
	std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
	double density = 0;

	for (int i = 0; i <listNeighbours.size(); i++)
	{
		r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
		density += listNeighbours[i]->getMass()*Poly6_kernel(r,h);
	}

	return density;
}

// Calculate pressure for each particle(at that position of that particle)
  double calculatePressure(Particle* particle) {
	  return STIFFNESS_PARAMETER*(particle->getDensity() - REST_DENSITY);
   }
    
   double calculateLaplacianPressure(Particle* particle){
        double laplacian = 0;

        // See p.33
        for(int i = 0; i < NUM_NEIGHBOURING_PARTICLES; i++)
        {
            float dx = x - particles[i].x;
            float dy = y - particles[i].y;
            float dz = z - particles[i].z;
            float distance = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
            if (distance >= 0 && distance < RADIUS)
            {
                // Using the gradient of the poly6 smoothing kernel, see p.30
                float sk = (315.f / (64.f * PI * powf(RADIUS, 9.f))) *
                (3.f * powf(powf(RADIUS, 2.f) - powf(distance, 2.f), 2.f)) * (-2.f * distance);
                
                laplacian += (1.f / particles[i].density ) * particles[i].pressure * sk;
            }
        }
        
        laplacian *= PARTICLE_MASS;
        
        return laplacian;
    }
    
    void compute_density_and_pressure(){
     
        for(int i = 0; i < MAX_PARTICLES; i++)
        {
            Particle* neighbors = find_neighborhood();
            
            float d = compute_density(neighbors);
            compute_pressure(d);
            compute_laplacian_of_pressure(neighbors);
        }
    }

	//TODO: Ning's force dencity
	void compute_force_dencity(Particle* particles){
		float mFx = 0, mFy = 0, mFz = 0;
		for (int i = 0; i < NUM_NEIGHBOURING_PARTICLES; i++)
		{
			float dx = x - particles[i].x;
			float dy = y - particles[i].y;
			float dz = z - particles[i].z;
			float distance = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
			float weight;
			//presure part: - gradient p
			weight = spiky_kernel_gradient(distance);
			float mFp = -PARTICLE_MASS / particles[i].density*(pressure - particles[i].pressure)*weight;
			mFx += mFp*dx;
			mFy += mFp*dy;
			mFz += mFp*dz;

			//viscocity part: nu laplacia u
			weight = viscous_kernel(distance);
			mFx += VISCOUSITY_COEFFICIENT*PARTICLE_MASS*(particles[i].vx - vx) / particles[i].density*weight;
			mFy += VISCOUSITY_COEFFICIENT*PARTICLE_MASS*(particles[i].vy - vy) / particles[i].density*weight;
			mFz += VISCOUSITY_COEFFICIENT*PARTICLE_MASS*(particles[i].vz - vz) / particles[i].density*weight;
		}
		//gravity part: g
		mFy += density*GRAVITY_COEFFICIENT*-1;

		// force dencity
		fx = mFx;
		fy = mFy;
		fz = mFz;
	}

	void compute_force_dencity(){

		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			Particle* neighbors = find_neighborhood();
			compute_force_dencity(neighbors);
		}
	}
	// End TODO Ning
    
};

//TODO: Ning's spiky kernel and viscous kernel

// End TODO Ning


Particle particleContainer[MAX_PARTICLES];



void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere(0.05, 100, 100);
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Fluid Simulation");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    
    glutMainLoop();
    
    return 0;
}
