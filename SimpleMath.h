#ifndef SIMPLEMATH_H
#define SIMPLEMATH_H

#include <math.h>
#include <cstring>

const double PI = 3.14159;
//Points
struct Point3{
	double x, y, z;
	Point3(){
		x = 0;
		y = 0;
		z = 0;
	}
	Point3(double a, double b, double c) :x(a), y(b), z(c){}
};

//Vectors
struct Vec3
{
	double x, y, z;
	Vec3() { x = 0; y = 0; z = 0; }
	Vec3(double a, double b, double c) :x(a), y(b), z(c){}
};

struct Vec4
{
	double x, y, z, w;
	Vec4() { x = 0; y = 0; z = 0; w = 0; }
	Vec4(double a, double b, double c, double d) :x(a), y(b), z(c), w(d){}
};

struct Vec2
{
	double x, y;
	Vec2() { x = 0; y = 0; }
	Vec2(double a, double b) :x(a), y(b){}
};

struct Mat3
{
	double values[9];
	Mat3()
	{
		for (unsigned i = 0; i<9; i++)
			values[i] = 0;
	}
};

struct Mat4
{
	double values[16];
	Mat4()
	{
		for (unsigned i = 0; i<16; i++)
			values[i] = 0;
	}
};

void trans(float* m, float* v, float* r);
void axisToMat(float* a, float ang, float* m);
void mult(float* m1, float* m2, float* r);
void mult(double* m1, float* m2, double* r);
void multv(float *m, float *v, float *r, float w = 1.0);
void scalar(float s, float* m, float *r);
void add(float *s, float*m, float *r);

//Vector operations
double dot2(Vec2 a, Vec2 b);

double dot3(Vec3 a, Vec3 b);

double dot4(Vec4 a, Vec4 b);

Vec3 difPoint3(Point3 A, Point3 B);

Vec3 difVec3(Vec3 u, Vec3 v);
Vec3 sumVec3(Vec3 A, Vec3 B);

Vec3 multscalarVec3(Vec3 A, double b);

Vec4 sumVec4(Vec4 A, Vec4 B);

Vec3 cross3(Vec3 a, Vec3 b);

double normVec3(Vec3 u);

double distanceVec3(Vec3 u, Vec3 v);

Vec4 multscalarVec4(Vec4 A, double b);

Vec3 multscalarVec3(Vec3 A, double b);

//Matrix operations

Mat4 multMatrix4(Mat4 A, Mat4 B);

Vec4 multMatrix4Vec4(Mat4 A, Vec4 b);

Mat4 getIdentityMatrix4();

Mat4 multscalarMat4(Mat4 A, double b);

Mat4 sumMatrix4(Mat4 A, Mat4 B);

void invertMatrix(const double * m, double * out);

#endif
