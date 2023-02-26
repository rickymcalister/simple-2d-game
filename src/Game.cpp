#include "Game.h"

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Simple 2D Game", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

// Functions
void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    /*
     * Render Game Objects
     *
     * - Clear old frame
     * - Render objects
     * - Display frame in window
     */
    this->window->clear(sf::Color(255, 0, 0, 255));

    // Draw game objects

    this->window->display();
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}


