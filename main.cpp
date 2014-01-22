#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Terrain.h"
#include "World.h"

#define FPS 60.0f;
float sleep = 1.0f/FPS;

int main(int, char const**)
{
    sf::Vector2i screenDimensions(1280, 720);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Tanks");
    World map = *new World();
    
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                map = *new World();
            }
        }

        // Clear screen
        window.clear(sf::Color(0,230,230));
        
        Terrain terrain(screenDimensions, &map);
        
        window.draw(terrain);
        
        window.display();
        
        sf::sleep(sf::seconds(sleep));
    }
    
    return EXIT_SUCCESS;
}
