#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Terrain.h"
#include "World.h"
#include "Missile.h"

#define FPS 120.0f;
float sleep = 1.0f/FPS;

sf::Clock Clock;

const float Speed = 120.f;

int main(int, char const**)
{
    sf::Vector2i screenDimensions(1280, 720);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Tanks");
    World *map = new World();
    
    Terrain *terrain = new Terrain(screenDimensions, map);
    Missile *missile = new Missile(100, 45, sf::Vector2i(21,699), screenDimensions, map);
    
    srand(time(NULL));
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Espace pressed : exit
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                window.close();
            }
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                delete map;
                map = new World();
                terrain = new Terrain(screenDimensions, map);
            }
            
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                missile = new Missile(rand()%75+50, rand()%80, sf::Vector2i(21,699), screenDimensions, map);
            }
        }

        // Clear screen
        window.clear(sf::Color(0,230,230));
        
        window.draw(*terrain);
        
        missile->prepareForLaunch();
        
        window.draw(*missile);
        
        window.display();
        
        missile->incrementTime(Clock.getElapsedTime());
        Clock.restart();
        sf::sleep(sf::seconds(sleep));
    }
    
    return EXIT_SUCCESS;
}
