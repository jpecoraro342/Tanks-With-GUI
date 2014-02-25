/*
 * File:   Missile.h
 * Author: Joseph
 *
 * Created on January 9, 2013, 3:53 PM
 */

#ifndef MISSILE_H
#define	MISSILE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "World.h"

class Missile : public sf::Drawable {
public:
    Missile(sf::Vector2i screenDimensions, World *world, int velocity, int angle, sf::Vector2i initLocation);
    float getXPosition();
    float getYPosition();
    void calcXVelocity();
    void calcinitYVelocity();
    void degreesToRadians();
    void findYVeloc();
    void calcYVelocity();
    void prepareForLaunch();
    void incrementTime(sf::Time t);
    
    virtual ~Missile();
private:
    int initxPos;
    int inityPos;
    int currentx;
    int currenty;
    int initialVelocity;
    float initYVelocity;
    float yVelocity;
    float xVelocity;
    int angleDegrees;
    float angleRadians;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color missileColor = sf::Color(100,100,100);
    sf::Vector2i sd;
    World *w;
    float time;
    int radius;
};

#endif	/* MISSILE_H */

