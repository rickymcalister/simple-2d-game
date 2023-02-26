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

    this->window->setFramerateLimit(60);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Blue);
    this->enemy.setOutlineThickness(1.f);
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

void Game::updateMousePositions()
{
    /** 
     * Updates the mouse positions:
     * - Mouse Position Relative to Window (Vector2i)
     */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();
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
    this->window->clear();

    // Draw game objects
    this->window->draw(this->enemy);

    this->window->display();
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}
