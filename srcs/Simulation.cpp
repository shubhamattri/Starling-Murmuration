#include <iostream>
#include "flockofboids.h"
#include "boidrules.h"
#include "vectorfunc.h"
#include "Simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <ctime>
#include <cstdlib>

///SFML window
Simulation::Simulation()
{ this->sizeofboids = 3.0;
    this->window.create(sf::VideoMode(1920, 1080, 32), "Starling Murmuration Simulation", sf::Style::Default);
}

/// Run the starling simulation. 
void Simulation::Run()
{
    for (int i = 0; i < 0; i++) {
        boidrules b(1920 / 3, 1080 / 3); /// Starts all boids from the center of the screen
        sf::CircleShape shape(8,5);

      
        shape.setPosition(window_width, window_height); /// starts all shapes from the center of screen.
        shape.setOutlineColor(sf::Color(0,255,0));
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(3);

        /// Add boid shapes to the vector
        flock.adjoin_boid(b);
        shapes.push_back(shape);
    }
    while (window.isOpen()) {
    	
        ManageInput();
         
        Render();
    }
}

void Simulation::ManageInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::BackSpace) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::X))
             {
            window.close();
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    	
        ///  mouse coordinates as location
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
        boidrules b(mouseCoords.x, mouseCoords.y, false);
        sf::CircleShape shape(0,3);

        ///  visual parameters
        shape.setPosition(mouseCoords.x, mouseCoords.y);
        shape.setOutlineColor(sf::Color(255, 0, 0));
        shape.setFillColor(sf::Color(rand()%255, rand()%255, rand()%255));
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(0.2);
        shape.setRadius(4);

        /// Adds and shape to vector
        flock.adjoin_boid(b);
        shapes.push_back(shape);

        
        window.draw(shapes[shapes.size()-1]);
    }
}

void Simulation::Render()
{
    

    window.clear();

    /// Draws all of the Boids out, and applies functions that are needed to update.
    for (int i = 0; i < shapes.size(); i++) {
        window.draw(shapes[i]);

        /// location match
        shapes[i].setPosition(flock.boid_in_flock(i).location.x, flock.boid_in_flock(i).location.y);

        ///velocity direction angle
        double theta = flock.boid_in_flock(i).boidvelocity_angle(flock.boid_in_flock(i).velocity);
        shapes[i].setRotation(theta);

        /// wrapping
        ///  right boundary
        if (shapes[i].getPosition().x > window_width)
            shapes[i].setPosition(shapes[i].getPosition().x - window_width, shapes[i].getPosition().y);
        /// wrapping bottom boundary
        if (shapes[i].getPosition().y > window_height)
            shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - window_height);
        /// wrapping left boundary
        if (shapes[i].getPosition().x < 0)
            shapes[i].setPosition(shapes[i].getPosition().x + window_width, shapes[i].getPosition().y);
        /// wrapping top boundary
        if (shapes[i].getPosition().y < 0)
            shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + window_height);
    }
    flock.recursive_flocking();
	    window.display();
}
