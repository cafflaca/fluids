#include "SimpleMath.h"

double dot2(Vec2 a, Vec2 b)
{
	return a.x*b.x + a.y*b.y;
};

double dot3(Vec3 a, Vec3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
};

double dot4(Vec4 a, Vec4 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
};

void axisToMat(float* a, float ang, float* m)
{
	float t = 1 - cos(ang);
	float x = a[0];
	float y = a[1];
	float z = a[2];
	float c = cos(ang);
	float s = sin(ang);

	m[0] = t*x*x + c;
	m[1] = t*x*y + z*s;
	m[2] = t*x*z - y*s;
	m[3] = 0.0;
	m[4] = t*x*y - z*s;
	m[5] = t*y*y + c;
	m[6] = t*y*z + x*s;
	m[7] = 0.0;
	m[8] = t*x*z + y*s;
	m[9] = t*y*z - x*s;
	m[10] = t*z*z + c;
	m[11] = 0.0;
	m[12] = m[13] = m[14] = 0.0;
	m[15] = 1.0;
}

void trans(float* m, float* v, float* r)
{
	float p[16];

	for (int i = 0; i<16; ++i)
		p[i] = 0.0;
	p[0] = p[5] = p[10] = p[15] = 1.0;

	p[12] = v[0];
	p[13] = v[1];
	p[14] = v[2];

	mult(m, p, r);
}

void mult(float* m1, float* m2, float* r)
{
	float p[16];

	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			p[i * 4 + j] = 0;
			for (int x = 0; x<4; ++x)
				p[i * 4 + j] += m1[j + 4 * x] * m2[i * 4 + x];
		}
	}

	memcpy(r, p, sizeof(float)* 16);
}

void mult(double* m1, float* m2, double* r)
{
	double p[16];

	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			p[i * 4 + j] = 0;
			for (int x = 0; x<4; ++x)
				p[i * 4 + j] += m1[j + 4 * x] * m2[i * 4 + x];
		}
	}

	memcpy(r, p, sizeof(double)* 16);
}

void multv(float *m, float *v, float *r, float w)
{
	float t[3];

	t[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * w;
	t[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * w;
	t[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * w;

	memcpy(r, t, sizeof(float)* 3);
}

void scalar(float s, float* m, float *r)
{
	for (int i = 0; i<16; ++i)
		r[i] = m[i] * s;
}

void add(float* s, float* m, float *r)
{
	for (int i = 0; i<16; ++i)
		r[i] = m[i] + s[i];
}

Vec3 difPoint3(Point3 A, Point3 B) {
	return Vec3(A.x - B.x, A.y - B.y, A.z - B.z);

}

Vec3 cross3(Vec3 a, Vec3 b){

	return Vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - b.x*a.y);

}

Vec3 difVec3(Vec3 u, Vec3 v){
	return Vec3(u.x-v.x,u.y-v.y,u.z-v.z);
}

double normVec3(Vec3 u){
	return sqrt( dot3(u,u));
}


//To improve with loops
Mat4 multMatrix4(Mat4 A, Mat4 B){
	Mat4 C;


	C.values[0] = A.values[0] * B.values[0] + A.values[1] * B.values[4] + A.values[2] * B.values[8] + A.values[3] * B.values[12];
	C.values[1] = A.values[0] * B.values[1] + A.values[1] * B.values[5] + A.values[2] * B.values[9] + A.values[3] * B.values[13];
	C.values[2] = A.values[0] * B.values[2] + A.values[1] * B.values[6] + A.values[2] * B.values[10] + A.values[3] * B.values[14];
	C.values[3] = A.values[0] * B.values[3] + A.values[1] * B.values[7] + A.values[2] * B.values[11] + A.values[3] * B.values[15];

	C.values[4] = A.values[4] * B.values[0] + A.values[5] * B.values[4] + A.values[6] * B.values[8] + A.values[7] * B.values[12];
	C.values[5] = A.values[4] * B.values[1] + A.values[5] * B.values[5] + A.values[6] * B.values[9] + A.values[7] * B.values[13];
	C.values[6] = A.values[4] * B.values[2] + A.values[5] * B.values[6] + A.values[6] * B.values[10] + A.values[7] * B.values[14];
	C.values[7] = A.values[4] * B.values[3] + A.values[5] * B.values[7] + A.values[6] * B.values[11] + A.values[7] * B.values[15];

	C.values[8] = A.values[8] * B.values[0] + A.values[9] * B.values[4] + A.values[10] * B.values[8] + A.values[11] * B.values[12];
	C.values[9] = A.values[8] * B.values[1] + A.values[9] * B.values[5] + A.values[10] * B.values[9] + A.values[11] * B.values[13];
	C.values[10] = A.values[8] * B.values[2] + A.values[9] * B.values[6] + A.values[10] * B.values[10] + A.values[11] * B.values[14];
	C.values[11] = A.values[8] * B.values[3] + A.values[9] * B.values[7] + A.values[10] * B.values[11] + A.values[11] * B.values[15];

	C.values[12] = A.values[12] * B.values[0] + A.values[13] * B.values[4] + A.values[14] * B.values[8] + A.values[15] * B.values[12];
	C.values[13] = A.values[12] * B.values[1] + A.values[13] * B.values[5] + A.values[14] * B.values[9] + A.values[15] * B.values[13];
	C.values[14] = A.values[12] * B.values[2] + A.values[13] * B.values[6] + A.values[14] * B.values[10] + A.values[15] * B.values[14];
	C.values[15] = A.values[12] * B.values[3] + A.values[13] * B.values[7] + A.values[14] * B.values[11] + A.values[15] * B.values[15];

	return C;

}

Vec4 multMatrix4Vec4(Mat4 A, Vec4 b){
	Vec4 c;
	c.x = A.values[0] * b.x + A.values[1] * b.y + A.values[2] * b.z + A.values[3] * b.w;
	c.y = A.values[4] * b.x + A.values[5] * b.y + A.values[6] * b.z + A.values[7] * b.w;
	c.z = A.values[8] * b.x + A.values[9] * b.y + A.values[10] * b.z + A.values[11] * b.w;
	c.w = A.values[12] * b.x + A.values[13] * b.y + A.values[14] * b.z + A.values[15] * b.w;

	return c;
}


Mat4 getIdentityMatrix4(){

	Mat4 identity;

	identity.values[0] = identity.values[5] = identity.values[10] = identity.values[15] = 1;
	return identity;


}

Vec4 multscalarVec4(Vec4 A, double b){

	return Vec4(A.x*b, A.y*b, A.z*b, A.w*b);
}

Vec3 multscalarVec3(Vec3 A, double b){
    
    return Vec3(A.x*b, A.y*b, A.z*b);
}

Vec4 sumVec4(Vec4 A, Vec4 B){

	return Vec4(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
}

Vec3 sumVec3(Vec3 A, Vec3 B){
	return Vec3(A.x + B.x, A.y + B.y, A.z + B.z);
}

/*Vec3 multscalarVec3(Vec3 A, double b){
	return Vec3(b*A.x,b*A.y,b*A.z);
}*/

Mat4 sumMatrix4(Mat4 A, Mat4 B){
	Mat4 C;
	for (unsigned i = 0; i < 16; i++){
		C.values[i] = A.values[i] + B.values[i];
	}
	return C;
}


Mat4 multscalarMat4(Mat4 A, double b){
	Mat4 C;
	for (unsigned i = 0; i < 16; i++){
		C.values[i] = A.values[i] * b;
	}
	return C;

}

double distanceVec3(Vec3 u, Vec3 v){
    return 	sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2) + pow(u.y - v.y, 2));
}

