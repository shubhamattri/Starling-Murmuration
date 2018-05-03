#include<iostream>
#include"vectorfunc.h"
#include<math.h>
#define pi 3.141592635

///functions of vectorfunc.h

void vectorfunc::set_xy(double a, double b){x = a; y = b;}

void vectorfunc::normalize_vec()///set values of x and y after normalizing it vector's magnitude
{
	double vec_mag = magnitude();
	if(vec_mag > 0){set_xy(x/vec_mag ,y/vec_mag);}  else{set_xy(x,y);}
}

void vectorfunc::set_magnitude(double scale){normalize_vec(); scalar_multiplication(scale);}///sets magnitude of vector

void vectorfunc::max_limit(double M)
{
	double val = magnitude();
	if(val > M){set_xy(x/val, y/val);}
}

vectorfunc vectorfunc::replicate_vec(vectorfunc vec)///makes a copy of a vector
{
	vectorfunc replicate_vec(vec.x, vec.y);
	return replicate_vec;
}

void vectorfunc::vector_addition(vectorfunc vec){x = x + vec.x ; y = y + vec.y; }///adds vector's x and y to given x and y
void vectorfunc::scalar_addition(double scalar){x = x + scalar; y = y + scalar; }///adds scalar to vector's x and y
void vectorfunc::vector_sub(vectorfunc vec){x = x - vec.x; y = y - vec.y; }///subtracts vector's x and y from given x and y
void vectorfunc::scalar_sub(double scalar){x = x - scalar; y = y - scalar;}///subtracts vector's x and y from scalar

vectorfunc vectorfunc::two_vec_sub(vectorfunc vec, vectorfunc vec1)///subtracts two input vectors
{
	vectorfunc v;
	vec.x = vec.x-vec1.x; vec.y = vec.y-vec1.y;
	v.set_xy(vec.x,vec.y);
	return v;
}

void vectorfunc::vector_multiplication(vectorfunc vec){x = x*vec.x; y = y*vec.y; }///multiplies vector to given vector
void vectorfunc::scalar_multiplication(double scalar){x = x*scalar; y = y*scalar; }///adds vector by scalar
void vectorfunc::vector_division(vectorfunc vec){x = x/vec.x; y = y/vec.y; }///divides vector by given vector
void vectorfunc::scalar_division(double scalar){x = x/scalar; y = y/scalar; }///divides vector by scalar

double vectorfunc::magnitude(){return sqrt(x*x + y*y);}///calculates magnitude of a vector

double vectorfunc::distance_betn_vec(vectorfunc vec)///calculates distance between two vectors
{
	double x_sub,y_sub ;
	x_sub = x-vec.x; y_sub = y-vec.y;
	return sqrt(x_sub*x_sub + y_sub*y_sub);
}

double vectorfunc::dot_prod(vectorfunc vec)///takes dot product of two vectors and returns it
{
	double dp = x*vec.x + y*vec.y;
	return dp;
}

double vectorfunc::angle_betn_vec(vectorfunc vec)///returns angle between two vectors
{
	if( (x == 0 && y == 0) || (vec.x == 0 && vec.y == 0) ) return 0;
	///using dot product concept to calculate angle between two vectors
	double prod_vec_mag = (sqrt(x*x + y*y) * sqrt(vec.x*vec.x + vec.y*vec.y));
	double dot_prod = x*vec.x + y*vec.y;
	double p = dot_prod/prod_vec_mag ;
	if(p<=-1){return pi;} else if(p>=1){return 0;}
	double cos_inv_p = acos(p);
	return cos_inv_p;
}















