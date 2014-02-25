//
//  Tanks.cpp
//  Tanks GUI
//
//  Created by Joseph Pecoraro on 2/25/14.
//  Copyright (c) 2014 Joseph Pecoraro. All rights reserved.
//

#include "Tank.h"
#include "World.h"



Tank::Tank(sf::Vector2i screenDimensions, World *world, sf::Color tColor, int x, int y) {
    sd = screenDimensions;
    w = world;
    tankColor = tColor;
    xPos = x;
    yPos = y;
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tankBody;
    tankBody.setSize(sf::Vector2f(tLength, tHeight));
    tankBody.setFillColor(tankColor);
    tankBody.setPosition(sf::Vector2f(xPos,yPos));
    
    sf::RectangleShape tankCannon;
    tankCannon.setSize(sf::Vector2f(20,2));
    tankCannon.setFillColor(tankColor);
    tankCannon.rotate(-30);
    tankCannon.setPosition(sf::Vector2f(xPos+10,yPos+8));
    
    target.draw(tankCannon, states);
    target.draw(tankBody, states);
    
}