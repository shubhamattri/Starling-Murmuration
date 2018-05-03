#include <iostream>
#include "flockofboids.h"
#include "boidrules.h"
#include "vectorfunc.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {
private:
    sf::RenderWindow window;
    int window_width;
    int window_height;
    sf::Texture pTexture;
    sf::Sprite pImage;

    flockofboids flock;
    double sizeofboids;
    vector<sf::CircleShape> shapes;

    void Render();
    //void Display_image();
    void ManageInput();

public:
    Simulation();
    void Run();
};

#endif
