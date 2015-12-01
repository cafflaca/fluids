#include <iostream>
#include <math.h>
#include "Particle.h"
#include "Kernel.h"
#include "Integration.h"
#include "Collision.h"

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
const double GRAVITY_COEFFICIENT = 9.819;
const double VISCOUSITY_COEFFICIENT = 0.0091;

int oldTime;
bool startAnimation;

//Calculate density for each particle (at that position of that particle)
double calculateDensity(Particle* particle) {
    double h = PARTICLE_RADIUS * 3;//1.0; // radius aroun a given particle to look out for neighbours
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
		Vec3 r;
		double h = PARTICLE_RADIUS * 3;//1.0;
		std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
        // See p.33
		for (unsigned i = 0; i < listNeighbours.size(); i++)
        {
			r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
			laplacian += (1.0 / listNeighbours[i]->getDensity()) * listNeighbours[i]->getPressure() * Poly6_kernel_gradient(r, h);
            
        }
        
        laplacian *= particle->getMass();
        
        return laplacian;
    }

    
    /*void compute_density_and_pressure(){
     
        for(int i = 0; i < MAX_PARTICLES; i++)
        {
            Particle* neighbors = find_neighborhood();
            
            float d = compute_density(neighbors);
            compute_pressure(d);
            compute_laplacian_of_pressure(neighbors);
        }
    }*/

	//TODO: Ning's force dencity
	Vec3 compute_force_density(Particle* particle){
		Vec3 mF;
		double mFp; // You have to initialize please, I dont know if you initialize this variable.
		double h = PARTICLE_RADIUS * 3;//1.0; // radius aroun a given particle to look out for neighbours
		Vec3 r;
		std::vector<Particle*> listNeighbours = particle->find_neighborhood(h);
		double weight;
		//float mFx = 0, mFy = 0, mFz = 0;
		for (int i = 0; i < listNeighbours.size(); i++)
		{
			r = difVec3(particle->getPosition(), listNeighbours[i]->getPosition());
			
			//presure part: - gradient p
			weight = spiky_kernel_gradient(r,h);
			mFp = -particle->getMass() / listNeighbours[i]->getDensity()*(particle->getPressure() - listNeighbours[i]->getPressure())*weight;
			mF.x += mFp*r.x;
			mF.y += mFp*r.y;
			mF.z += mFp*r.z;

			//viscocity part: nu laplacia u
			weight = viscous_kernel(r,h);
			mF.x += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().x - particle->getVelocity().x) / listNeighbours[i]->getDensity()*weight;
			mF.y += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().y - particle->getVelocity().y) / listNeighbours[i]->getDensity()*weight;
			mF.z += VISCOUSITY_COEFFICIENT*particle->getMass()*(listNeighbours[i]->getVelocity().z - particle->getVelocity().z) / listNeighbours[i]->getDensity()*weight;
		}
		//gravity part: g
		mF.y += particle->getDensity()*GRAVITY_COEFFICIENT*-1;

		// force density
		Vec3 force;
		force.x = mF.x;
		force.y = mF.y;
		force.z = mF.z;
        
        return force;
	}

	/*void compute_force_dencity(){

		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			Particle* neighbors = find_neighborhood();
			compute_force_dencity(neighbors);
		}
	}
	// End TODO Ning
    
};*/

//TODO: Ning's spiky kernel and viscous kernel

// End TODO Ning


//Particle particleContainer[MAX_PARTICLES];

void set_initial_particle_positions(){
    Vec3 initialVelocity = Vec3(0, 0, 0);
    
    for (int k = 0; k < PARTICLE_BLOCK_HEIGHT; k++) {
        for (int j = 0; j < PARTICLE_BLOCK_WIDTH; j++) {
            for (int i = 0; i < PARTICLE_BLOCK_LENGTH; i++) {
                new Particle(
                        Vec3(
                            (double)((double)i * PARTICLE_RADIUS * 2.0),
                            (double)j * PARTICLE_RADIUS * 2.0,
                            (double)k * PARTICLE_RADIUS * 2.0
                            ),
                            initialVelocity);
            }
        }
    }
}

void draw_particles() {
    Vec3 pos = Vec3(0, 0, 0);
    
    for (int i = 0; i < Particle::particles.size(); i++) {
        glPushMatrix();
        glLoadIdentity();
        pos = Particle::particles[i]->position;
        glTranslated(pos.x, pos.y, pos.z);
        glutSolidSphere(0.05, 100, 100);
        glPopMatrix();
    }
    glPopMatrix();
}

void initialize() {
    set_initial_particle_positions();
    startAnimation = false;
    oldTime = 0;
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        case 32:
            startAnimation ? startAnimation = false : startAnimation = true;
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double newTime = glutGet(GLUT_ELAPSED_TIME);
    double timeStep = 0.03;//newTime - oldTime;
    Vec3 force;
    int size = Particle::particles.size();
    int i;
    for (i = 0; i < size; i++) {
        Particle::particles[i]->find_neighborhood(PARTICLE_RADIUS * 3);
        //cout << " PASS 1" << endl;
    }
    
    for (i = 0; i < size; i++) {
        calculateDensity(Particle::particles[i]);
        Particle::particles[i]->pressure = calculatePressure(Particle::particles[i]);
        calculateLaplacianPressure(Particle::particles[i]);
        //cout << " PASS 2" << endl;
    }
    
    for (i = 0; i < size; i++) {
        Particle::particles[i]->force_densities = compute_force_density(Particle::particles[i]);
        //cout << " PASS 3" << endl;
    }
    
    for (i = 0; i < size; i++) {
        Vec3 velocity = nextVelocity(Particle::particles[i], Particle::particles[i]->force_densities, timeStep);
        nextStep(Particle::particles[i], velocity, timeStep);
        //handle_collision(Particle::particles[i], detect_particle_collision(Particle::particles[i]), timeStep);
        //handle_collision(Particle::particles[i], detect_boundary_collision(Particle::particles[i]), timeStep);
        //cout << " PASS 4" << endl;
    }
    
    draw_particles();
    
    oldTime = newTime;
    cout << " PASS" << endl;
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Fluid Simulation");
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    
    glutMainLoop();
    
    return 0;
}
