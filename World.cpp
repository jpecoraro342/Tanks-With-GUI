/*
 * File:   World.cpp
 * Author: Joseph
 *
 * Created on January 9, 2013, 12:55 AM
 */

#include "World.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

World::World() {
    playersInWorld = *new vector<Player*>();
    width = 64;
    height = 36;
    grid = new char*[width+1];
    tHeight = new int[width+1];
    
    for(int i = 0; i <= width; i++) {
        grid[i] = new char[height];
    }
    addSpaces();
    generateTerrain();
}

World::~World() {
}

//generates terrain. First picks random y start point 15-75(to be subtracted by height later. Then for each x value, 0,1,or-1 is randomly generated. The terrain will then act accordingly increasing the y value by 1, keeping it the same, or decreasing by one. bounds are applied 15-75
void World::generateTerrain() {
	srand(time(0));
    int indices[width+1];
    int starter = rand() %5 + 8; //generate random number from 15-75 for starting vertex this is equivalent pixels 75-375
    int change;
    int value;
    indices[0] = starter;
    tHeight[0] = starter;
    
    for (int i = 1; i <= width; i ++) {
        change = rand() % 3 -1;
        value = indices[i-1] + change;
        indices[i]=value;
        tHeight[i]=value;
    }
    
    for (int i = 0; i < width; i++) {
        grid[i][indices[i]] = 'T';
    }
}

//prints the world
void World::printWorld() {
    for (int i =0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            cout << grid[j][i];
        }
        cout << " " << endl;
    }
}

//adds spaces to each char in the original grid world.
void World::addSpaces() {
    for (int i =0; i < width; i ++) {
        for (int j = 0; j < height; j ++) {
            grid[i][j] = ' ';
        }
    }
}

//adds player number n to the world at random x position
void World::addPlayer(Player &p, int n) {
    int xPos = rand() %98 + 1;
    char target = ' ';
    int yPos = 0;
    for (int i = 0; i < height; i ++) {
        target = grid[xPos][i];
        if (target == 'T') {
            yPos = i -2;
            break;
        }
    }
    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j++) {
            grid[xPos + i][yPos + j] = 'P';
        }
    }
    grid[xPos][yPos] = '0' + n;
    
    p.setXPosition(xPos);
    p.setYPosition(yPos);
    playersInWorld.push_back(&p);
}

//returns the player at the given x position. used for finding which player has been shot.
Player* World::getPlayer(int xPos) {
    for (int i =0; i < playersInWorld.size(); i ++) {
        if (playersInWorld[i]->hasX(xPos)) return playersInWorld[i];
    }
}

//checks if shot at given x,y position is less than or equal to Terrain or X(dead player)
bool World::xyIsLessEqualTX(int x, int y) {
    for (int i = 0; i < height; i ++) {
        if (grid[x][i] == 'T' || grid[x][i] == 'X') {
            if (y >= i) return true;
            else return false;
        }
    }
    return false;
}

//Checks to see if a shot at given x, y is less than or equal to a player
bool World::xyIsLessEqualP(int x, int y) {
    for (int i = 0; i < height; i ++) {
        if (grid[x][i] == 'P') {
            if (y >= i) return true;
            else return false;
        }
    }
    return false;
}

//adds a missile to the world that is shot from the player p. shot stops if x out of bounds, or above two methods true. if It hits player, the player is killed with the kill methods.
void World::addMissile(Missile m, Player p) {
    missileToGrid();
    int initx = p.getXPosition()+2;
    int inity = p.getYPosition()-1;
    int x = 0;
    int y = 0;
    for (int i = 0; i < width; i ++) {
        x += m.xVals[i];
        y += m.yVals[i];
        
        if (inity - y < 0) { }
        else if (initx+x < 0 || initx+x >99) break;
        else if (xyIsLessEqualTX(initx + x, inity - y))
            break;
        else if (xyIsLessEqualP(initx + x, inity - y)) {
            Player *p1 = getPlayer(initx + x);
            p1->kill(); //changes status of is alive
            int px = p1->getXPosition();
            int py = p1->getYPosition();
            killPlayer(px, py);
            break;
        }
        else worldPostMissile[initx + x][inity - y] = '.';
    }
}

//kills player at given x,y position by replacing the P's with X's
void World::killPlayer(int x, int y) {
    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j++) {
            grid[x + i][y + j] = 'X';
            worldPostMissile[x+i][y+j] = 'X';
        }
    }
}

//resets the world to its state without missiles
void World::missileToGrid() {
    for (int i =0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            worldPostMissile[j][i] = grid[j][i];
        }
    }
}

//prints the world post missile
void World::printMissileWorld() {
    for (int i =0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            cout << worldPostMissile[j][i];
        }
        cout << " " << endl;
    }
}

