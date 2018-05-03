#include<iostream>
#include<math.h>

using namespace std;

#ifndef VECTORFUNC_H_
#define VECTORFUNC_H_

class vectorfunc{
public:
	double x; 
	double y;

	///constructors of vector functions
	vectorfunc() {}
	vectorfunc(double a, double b )
	{
		x = a; y = b;
	}


	void set_xy(double x, double y);///sets new value of x and y co-ordinates
	void normalize_vec();
	void set_magnitude(double mag);

	void max_limit(double M);
	vectorfunc replicate_vec(vectorfunc vec);


	void vector_addition(vectorfunc vec);
	void scalar_addition(double scalar);
	void vector_sub(vectorfunc vec);
	void scalar_sub(double scalar);
	vectorfunc two_vec_sub(vectorfunc vec, vectorfunc vec1);
	void vector_multiplication(vectorfunc vec);
	void scalar_multiplication(double scalar);
	void vector_division(vectorfunc vec);
	void scalar_division(double scalar);

	///calculation returning functions
	double magnitude();
	double distance_betn_vec(vectorfunc vec);
	double dot_prod(vectorfunc vec);
	double angle_betn_vec(vectorfunc vec);
};
#endif
