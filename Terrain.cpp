//
//  Terrain.cpp
//  SFML Tutorial 1
//
//  Created by Joseph Pecoraro on 11/13/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "Terrain.h"

Terrain::Terrain(sf::Vector2i screenDimensions, World *world) {
    sd = screenDimensions;
    w = world;
}

void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::VertexArray vertices(sf::PrimitiveType::TrianglesFan);
    
    vertices.append(sf::Vertex(sf::Vector2f(0, 720), terrainColor));
    for (int i = 0; i <= 64; i++) {
        vertices.append(sf::Vertex(sf::Vector2f(20*i, 720-20*w->tHeight[i]), terrainColor));
    }
    vertices.append(sf::Vertex(sf::Vector2f(1280, 720), terrainColor));
    target.draw(vertices, states);
}