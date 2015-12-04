#include <iostream>
#include <math.h>
#include "Particle.h"
#include "SPH.h"


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

bool startAnimation;
int oldTime;
//Model matrices
double _matrix[16];
double _matrixI[16];
/* Mouse Interface  */
int _mouseX = 0;		/* mouse control variables */
int _mouseY = 0;
bool _mouseLeft = false;
bool _mouseMiddle = false;
bool _mouseRight = false;


double _dragPosX = 0.0;
double _dragPosY = 0.0;
double _dragPosZ = 0.0;

//Window parameters
int width = 1024;
int height = 768;
///* Ortho (if used) */
double _left = 0.0;		/* ortho view volume params */
double _right = 0.0;
double _bottom = 0.0;
double _top = 0.0;
double _zNear = 0.1;
double _zFar = 50.0;
double fovy = 45.0;
double prev_z = 0;

/*void set_initial_particle_positions(){
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
}*/

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
	setInitialConditions();
	//testRun();
    startAnimation = false;
    oldTime = 0;
}


double vlen(double x, double y, double z)
{
	return sqrt(x * x + y * y + z * z);
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
	testRun();
    draw_particles();
    glutSwapBuffers();
    glutPostRedisplay();
}




void pos(double *px, double *py, double *pz, const int x, const int y,
	const int *viewport)
{
	/*
	Use the ortho projection and viewport information
	to map from mouse co-ordinates back into world
	co-ordinates
	*/

	*px = (double)(x - viewport[0]) / (double)(viewport[2]);
	*py = (double)(y - viewport[1]) / (double)(viewport[3]);

	*px = _left + (*px) * (_right - _left);
	*py = _top + (*py) * (_bottom - _top);
	*pz = _zNear;
}

void getMatrix()
{
	glGetDoublev(GL_MODELVIEW_MATRIX, _matrix);
	invertMatrix(_matrix, _matrixI);
}

void mouseMoveEvent(int x, int y)
{

	bool changed = false;

	const int dx = x - _mouseX;
	const int dy = y - _mouseY;

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (dx == 0 && dy == 0)
		return;

	if (_mouseMiddle || (_mouseLeft && _mouseRight)) {
		/* double s = exp((double)dy*0.01); */
		/* glScalef(s,s,s); */
		/* if(abs(prev_z) <= 1.0) */

		glLoadIdentity();
		glTranslatef(0, 0, dy * 0.01);
		glMultMatrixd(_matrix);

		changed = true;
	}
	else if (_mouseLeft) {
		double ax, ay, az;
		double bx, by, bz;
		double angle;

		ax = dy;
		ay = dx;
		az = 0.0;
		angle = vlen(ax, ay, az) / (double)(viewport[2] + 1) * 180.0;

		/* Use inverse matrix to determine local axis of rotation */

		bx = _matrixI[0] * ax + _matrixI[4] * ay + _matrixI[8] * az;
		by = _matrixI[1] * ax + _matrixI[5] * ay + _matrixI[9] * az;
		bz = _matrixI[2] * ax + _matrixI[6] * ay + _matrixI[10] * az;

		glRotatef(angle, bx, by, bz);

		changed = true;
	}
	else if (_mouseRight) {
		double px, py, pz;

		pos(&px, &py, &pz, x, y, viewport);

		glLoadIdentity();
		glTranslatef(px - _dragPosX, py - _dragPosY, pz - _dragPosZ);
		glMultMatrixd(_matrix);

		_dragPosX = px;
		_dragPosY = py;
		_dragPosZ = pz;

		changed = true;
	}

	_mouseX = x;
	_mouseY = y;

	if (changed) {
		getMatrix();
		glutPostRedisplay();
	}

	
}

void mouseEvent(int button, int state, int x, int y)
{
	int viewport[4];

	_mouseX = x;
	_mouseY = y;

	if (state == GLUT_UP)
		switch (button) {
		case GLUT_LEFT_BUTTON:
			_mouseLeft = false;
			break;
		case GLUT_MIDDLE_BUTTON:
			_mouseMiddle = false;
			break;
		case GLUT_RIGHT_BUTTON:
			_mouseRight = false;
			break;
	}
	else
		switch (button) {
		case GLUT_LEFT_BUTTON:
			_mouseLeft = true;
			break;
		case GLUT_MIDDLE_BUTTON:
			_mouseMiddle = true;
			break;
		case GLUT_RIGHT_BUTTON:
			_mouseRight = true;
			break;
		case 4:         //Zoomout
			glLoadIdentity();
			glTranslatef(0, 0, -0.1);
			glMultMatrixd(_matrix);
			getMatrix();
			glutPostRedisplay();
			break;
		case 3:         //Zoomin
			glLoadIdentity();
			glTranslatef(0, 0, 0.1);
			glMultMatrixd(_matrix);
			getMatrix();
			glutPostRedisplay();
			break;
		default:
			break;
			//std::cout<<button<<std::endl;
	}

	glGetIntegerv(GL_VIEWPORT, viewport);
	pos(&_dragPosX, &_dragPosY, &_dragPosZ, x, y, viewport);
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

	//mouse interface
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMoveEvent);

    
    glutMainLoop();
    
    return 0;
}
