#include <iostream>
#include <vector>
#include "boidrules.h"

#ifndef FLOCKOFBOIDS_H_
#define FLOCKOFBOIDS_H_

class flockofboids
{
public:
	vector<boidrules> fob;
///Constructors of flockofboids
	flockofboids(){}

	boidrules boid_in_flock(int bif);
	void adjoin_boid(boidrules b);
	//void remove_boid(boidrules b);
	void recursive_flocking();
	int flocksize();

};

#endif
