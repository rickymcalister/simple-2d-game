#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
    // Window Setup
    sf::RenderWindow window(sf::VideoMode(640, 480), "Simple 2D Game", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    // Game Loop
    while (window.isOpen())
    {
        // Event Polling
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
        }

        // Update


        // Render
        window.clear(sf::Color::Blue); // Clear the previous frame

        // Draw

        window.display(); // Display the current frame
    }

    // End of Application
    return 0;
}