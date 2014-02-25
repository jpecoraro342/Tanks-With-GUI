//
//  Terrain.h
//  SFML Tutorial 1
//
//  Created by Joseph Pecoraro on 11/13/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __SFML_Tutorial_1__Terrain__
#define __SFML_Tutorial_1__Terrain__

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "World.h"

class Terrain : public sf::Drawable {
    
public:
    Terrain(sf::Vector2i screenDimensions, World *world);
    Terrain() { sd = sf::Vector2i(1280, 720); }
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color terrainColor = sf::Color(55,204,80);
    sf::Vector2i sd; //screendimensions
    World *w;
    
};

#endif /* defined(__SFML_Tutorial_1__Terrain__) */
