/*
 * File:   Missile.cpp
 * Author: Joseph
 *
 * Created on January 9, 2013, 3:53 PM
 */

#define _USE_MATH_DEFINES
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Missile.h"
#include "World.h"
#include <math.h>

Missile::Missile(int velocity, int angle, sf::Vector2i initLocation, sf::Vector2i screenDimensions, World *world) {
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
    if (currentx-20 <= 0 || currentx+20 >=sd.x || currenty-20 <= 0 || currenty+20 >=sd.y) {
        return;
    }
    currentx = initxPos + getXPosition();
    currenty = inityPos - getYPosition();
}

void Missile::incrementTime(sf::Time t) {
    time += t.asSeconds()*10;
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::CircleShape missile(10);
    missile.setFillColor(sf::Color(100,100,100));
    missile.setPosition(sf::Vector2f(currentx, currenty));
    target.draw(missile);
}

