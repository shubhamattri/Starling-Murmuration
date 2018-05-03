
#include "boidrules.h"
#include "flockofboids.h"

boidrules flockofboids::boid_in_flock(int bif){ return fob[bif];}///returns the boid present in flock
void flockofboids::adjoin_boid(boidrules a_b){fob.push_back(a_b);}///adds boid to the vector data structure of boids
void flockofboids::recursive_flocking(){for (int i = 0; i < fob.size(); ++i){fob[i].execute_flocking(fob);}}///executes flocking on all the boids collection recursively 
int flockofboids::flocksize(){return fob.size();}///returns the size of flock