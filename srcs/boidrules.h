#include <iostream>
#include "vectorfunc.h"
#include <stdlib.h>
#include <vector>

#ifndef BOIDRULES_H_
#define BOIDRULES_H_


class boidrules
{
public:
	vectorfunc location;///location vector of boid
	vectorfunc acceleration;///acceleration vector of boid
	vectorfunc velocity;///velocity vector of boid
	double speed_limit;///speed vector limit 
	double force_limit;///since force = mass * acceleration (i.e acceleration vector limit)
	bool raptor;///boolean value such that -> Is the given boid a raptor or not?
///boidrules constructors
	boidrules(){}
	boidrules(double x,double y);
	boidrules(double x,double y, bool inspect_raptor);

///Functions which are used further for three boid rules and dispaying the boids on pc
	void wrapup_boids();///wrap up the boids around the window of desktop
	void modify();
	double boidvelocity_angle(vectorfunc vec);
	void applyrules_flock(vector<boidrules> vec);
	void execute_flocking(vector<boidrules> vec);


	///Three rules of boids which are followed by them
	///Each rule is required set of boids as input 
	vectorfunc Cohesion(vector<boidrules> boids);
	vectorfunc Seperation(vector<boidrules> boids);
	vectorfunc Alignment(vector<boidrules> boids);
    
    vectorfunc steer(vectorfunc vec);
	void accelerate_boid(vectorfunc force);

};

#endif
