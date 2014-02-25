/*
 * File:   Missile.cpp
 * Author: Joseph
 *
 * Created on January 9, 2013, 3:53 PM
 */

#define _USE_MATH_DEFINES
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Missile.h"
#include "World.h"
#include <math.h>

Missile::Missile(sf::Vector2i screenDimensions, World *world, int velocity, int angle, sf::Vector2i initLocation) {
    initialVelocity = velocity;
    angleDegrees = angle;
    degreesToRadians();
    calcXVelocity();
    calcinitYVelocity();
    currentx = initxPos = initLocation.x;
    currenty = inityPos = initLocation.y;
    sd = screenDimensions;
    w = world;
    time = 0;
    radius = 5;
}

Missile::~Missile() {
}

float Missile::getXPosition() {
    return xVelocity*time;
}

float Missile::getYPosition() {
    return (initYVelocity*time) - (.5*9.8*time*time);
}

void Missile::calcXVelocity() {
    xVelocity = initialVelocity*cos(angleRadians);
}

void Missile::calcinitYVelocity() {
    initYVelocity = initialVelocity*sin(angleRadians);
}

void Missile::calcYVelocity() {
    yVelocity = initYVelocity - 9.8*time;
}

void Missile::degreesToRadians() {
    angleRadians = angleDegrees*M_PI/180.0;
}

void Missile::prepareForLaunch() {
    if (currentx-2*radius <= 0) {
        currentx = 2*radius;
        return;
    }
    else if (currentx+2*radius >=sd.x) {
        currentx = sd.x-2*radius;
        return;
    }
    else if (currenty-2*radius <= 0) {
        currenty = 2*radius;
        return;
    }
    else if (currenty+2*radius >=sd.y) {
        currenty = sd.y-2*radius;
        return;
    }
    currentx = initxPos + getXPosition();
    currenty = inityPos - getYPosition();
}

void Missile::incrementTime(sf::Time t) {
    time += t.asSeconds()*10;
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::CircleShape missile(radius);
    missile.setFillColor(sf::Color(100,100,100));
    missile.setPosition(sf::Vector2f(currentx, currenty));
    target.draw(missile);
}

