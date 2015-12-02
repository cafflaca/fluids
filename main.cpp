#include <iostream>
#include <math.h>
#include "Particle.h"


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








   

    
    /*void compute_density_and_pressure(){
     
        for(int i = 0; i < MAX_PARTICLES; i++)
        {
            Particle* neighbors = find_neighborhood();
            
            float d = compute_density(neighbors);
            compute_pressure(d);
            compute_laplacian_of_pressure(neighbors);
        }
    }*/

	


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
