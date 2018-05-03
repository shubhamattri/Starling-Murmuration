#include<iostream>
#include "boidrules.h"
#include "SFML/Graphics.hpp"
#include <math.h>
#include <vector>
#define pi 3.141592635



sf::VideoMode screen = sf::VideoMode::getDesktopMode();///screen to be used as the features of desktop panel
const int height = screen.height;///height of desktop
const int width = screen.width;///width of desktop
///assigning short code name to height and width
#define h height
#define w width
///setting the physical parameters of a boid such as location , acceleration , velocity , speed_limit,force_limit
boidrules::boidrules(double x, double y){	location = vectorfunc(x,y);
											acceleration = vectorfunc(0,0);
											velocity =vectorfunc(rand()%3 - 2, rand()%3 - 2);
											speed_limit = 4.75;
											force_limit = 0.5;
										}
///trigger for enabling and disabling the raptor presence in the simulation
boidrules::boidrules(double x, double y, bool inspect_raptor){ raptor = inspect_raptor;
															   if(inspect_raptor == true){velocity = vectorfunc(rand()%3 - 1, rand()%3 - 1);
															   							  speed_limit = 4.75;
															   							  force_limit = 0.5;
															   							 } 
															   if(inspect_raptor == false){velocity = vectorfunc(rand()%3 - 2, rand()%3 - 2);
															   							  speed_limit = 2.75;
															   							  force_limit = 0.5;
															   							 }
															   location = vectorfunc(x,y);
															   acceleration = vectorfunc(0,0);
															 }															   
///two preserve the number of boids on the screen and creating a environment to move the flock by wrapping around the boundaries of screen
void boidrules::wrapup_boids(){if(location.x < 0)  {location.x = location.x + w;/*velocity =vectorfunc(-(rand()%3 - 2), -(rand()%3 - 2));*/} if(location.y < 0)    {location.y = location.y + h;/*velocity =vectorfunc(-(rand()%3 - 2), -(rand()%3 - 2));*/}
                               if(location.x > 1800){location.x = location.x - w;/*velocity =vectorfunc((rand()%3 - 2), (rand()%3 - 2));*/} if(location.y > 1000){location.y = location.y - h;/*velocity =vectorfunc((rand()%3 - 2), (rand()%3 - 2));*/}
							  
							  }
///to force the values of physical parameters required for the boids and modify them accordingly to execute flocking
void boidrules::modify(){acceleration.scalar_multiplication(0.4); velocity.vector_addition(acceleration);
						 velocity.max_limit(speed_limit);location.vector_addition(velocity);
						 acceleration.scalar_multiplication(0);
						}
///to calculate angle of velocity of boid for generating the motion of boids as per the boids rotation
///here angle is calculated using dot product rule					
double boidrules::boidvelocity_angle(vectorfunc vec){ double theta;
													  theta = double(atan2(vec.x, - vec.y) * 180 / pi);
													  return theta;
													}
///applying three folcking rules to the boids and setting their physical parameters
void boidrules::applyrules_flock(vector<boidrules> vec){ vectorfunc c = Cohesion(vec); vectorfunc s = Seperation(vec); vectorfunc a = Alignment(vec);
														 c.scalar_multiplication(1); s.scalar_multiplication(1.5); a.scalar_multiplication(1);
														 accelerate_boid(c); accelerate_boid(s); accelerate_boid(a);
}
///to display the actual boids set executing flocking applying all the rules , parameters updation and wrapping
void boidrules::execute_flocking(vector<boidrules> vec){applyrules_flock(vec); modify(); wrapup_boids();}


///steer towards average position of neighbours
vectorfunc boidrules::Cohesion(vector<boidrules> boids)
{
	double distance_of_neighbours = 50;
	vectorfunc goal(0,0);
	int neighbour_size = 0;
	for(int i = 0;i<boids.size();i++){
		double dist = location.distance_betn_vec(boids[i].location);
		if((dist > 0) && (dist < distance_of_neighbours)){goal.vector_addition(boids[i].location);
										                  neighbour_size++;
		                                                  }
	}
	if(neighbour_size > 0){goal.scalar_division(neighbour_size); return steer(goal);}
	else{vectorfunc gola(0,0); return gola;}
}


///Avoid crowding of neighbours
vectorfunc boidrules::Seperation(vector<boidrules> boids)
{
	double req_seperation = 20;
	vectorfunc goal(0,0);
	int count = 0;
    for (int i = 0; i < boids.size(); i++) {
        double dist = location.distance_betn_vec(boids[i].location);
        if ((dist > 0) && (dist < req_seperation)) 
        {
            vectorfunc diff(0,0);
            diff = diff.two_vec_sub(location, boids[i].location);
            diff.normalize_vec();
            diff.scalar_division(dist);      
            goal.vector_addition(diff);
            count++;
		}

		if ((dist > 0) && (dist < req_seperation) && boids[i].raptor == true && raptor == true) 
        {
            vectorfunc raptorVSraptor(0,0);
            raptorVSraptor = raptorVSraptor.two_vec_sub(location, boids[i].location);
            raptorVSraptor.normalize_vec();
            raptorVSraptor.scalar_division(dist);      
            goal.vector_addition(raptorVSraptor);
            count++;
		}

		if ((dist > 0) && (dist < req_seperation + 70) && boids[i].raptor == true) 
        {
            vectorfunc rapt(0,0);
            rapt = rapt.two_vec_sub(location, boids[i].location);
            rapt.scalar_multiplication(900);
            goal.vector_addition(rapt);
            count++;
		}
	}
	if(count > 0){goal.scalar_division((double)count);}
	if(goal.magnitude() > 0){goal.normalize_vec();
							 goal.scalar_multiplication(speed_limit);
							 goal.vector_sub(velocity);
							 goal.max_limit(force_limit);
	                        }
	return goal;
}	   

///steer towards average heading of neighbours
vectorfunc boidrules::Alignment(vector<boidrules> boids)
{
	double distance_of_neighbours = 50;
	vectorfunc velosum(0,0);
	int count;
	for (int i = 0; i < boids.size(); i++) {
        double dist = location.distance_betn_vec(boids[i].location);
        if ((dist > 0) && (dist < distance_of_neighbours)) { /// 0 < d < 50
            velosum.vector_addition(boids[i].velocity);
            count++;
        }
    }
    if(count > 0)
    {
    	velosum.scalar_division((double)count);
    	velosum.normalize_vec();
    	velosum.scalar_multiplication(speed_limit);
    	vectorfunc goal;
    	goal = goal.two_vec_sub(velosum,velocity);
    	goal.max_limit(force_limit);
    	return goal;
    }
    else{vectorfunc gola(0,0); return gola;}
}                    


///makes advancement of boid by getting the desired velocity,acceleration,force limit of steering force
vectorfunc boidrules::steer(vectorfunc vec)
{
	vectorfunc req;
	req.vector_sub(vec);
	req.normalize_vec();
	req.scalar_multiplication(speed_limit);
	acceleration.two_vec_sub(req,velocity);
	acceleration.max_limit(force_limit);
	return acceleration;
}

///increases the acceleration of boid
void boidrules::accelerate_boid(vectorfunc force){acceleration.vector_addition(force);}






