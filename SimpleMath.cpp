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


void invertMatrix(const double * m, double * out)
{

	/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

	/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)

	double det;
	double d12, d13, d23, d24, d34, d41;
	double tmp[16];		/* Allow out == in. */

	/* Inverse = adjoint / det. (See linear algebra texts.) */

	/* pre-compute 2x2 dets for last two rows when computing */
	/* cofactors of first two rows. */
	d12 = (m31 * m42 - m41 * m32);
	d13 = (m31 * m43 - m41 * m33);
	d23 = (m32 * m43 - m42 * m33);
	d24 = (m32 * m44 - m42 * m34);
	d34 = (m33 * m44 - m43 * m34);
	d41 = (m34 * m41 - m44 * m31);

	tmp[0] = (m22 * d34 - m23 * d24 + m24 * d23);
	tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
	tmp[2] = (m21 * d24 + m22 * d41 + m24 * d12);
	tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

	/* Compute determinant as early as possible using these cofactors. */
	det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

	/* Run singularity test. */
	if (det == 0.0) {
		/* printf("invert_matrix: Warning: Singular matrix.\n"); */
		/* 	  memcpy(out,_identity,16*sizeof(double)); */
	}
	else {
		double invDet = 1.0 / det;
		/* Compute rest of inverse. */
		tmp[0] *= invDet;
		tmp[1] *= invDet;
		tmp[2] *= invDet;
		tmp[3] *= invDet;

		tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
		tmp[5] = (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
		tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
		tmp[7] = (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

		/* Pre-compute 2x2 dets for first two rows when computing */
		/* cofactors of last two rows. */
		d12 = m11 * m22 - m21 * m12;
		d13 = m11 * m23 - m21 * m13;
		d23 = m12 * m23 - m22 * m13;
		d24 = m12 * m24 - m22 * m14;
		d34 = m13 * m24 - m23 * m14;
		d41 = m14 * m21 - m24 * m11;

		tmp[8] = (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
		tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
		tmp[10] = (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
		tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
		tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
		tmp[13] = (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
		tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
		tmp[15] = (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

		memcpy(out, tmp, 16 * sizeof(double));
	}

#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44
#undef MAT
}