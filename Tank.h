//
//  Tanks.h
//  Tanks GUI
//
//  Created by Joseph Pecoraro on 2/25/14.
//  Copyright (c) 2014 Joseph Pecoraro. All rights reserved.
//

#ifndef __Tanks_GUI__Tanks__
#define __Tanks_GUI__Tanks__

#include <SFML/Graphics.hpp>
#include "World.h"

class Tank : public sf::Drawable {
    
public:
    Tank(sf::Vector2i screenDimensions, World *world, sf::Color tColor, int x, int y);
    Tank() { sd = sf::Vector2i(1280, 720); }
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color tankColor;
    sf::Vector2i sd; //screendimensions
    World *w;
    const int tLength = 20;
    const int tHeight = 12;
    int xPos;
    int yPos;
    
};

#endif /* defined(__Tanks_GUI__Tanks__) */
