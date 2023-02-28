#include "Game.h"

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;

    // Game Logic
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->endGame - false;
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
    this->enemy.setFillColor(sf::Color::Cyan);
}

// Functions
void Game::spawnEnemy()
{
    /**
     * @brief Spawns an enemy and sets it's position randomly
     * @return void
     */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    int enemyType = rand() % 5;

    switch (enemyType)
    {
        case 0:
            this->enemy.setFillColor(sf::Color::Cyan);
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            break;
        case 1:
            this->enemy.setFillColor(sf::Color::Magenta);
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            break;
        case 2:
            this->enemy.setFillColor(sf::Color::Yellow);
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            break;
        case 3:
            this->enemy.setFillColor(sf::Color::Red);
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            break;
        case 4:
            this->enemy.setFillColor(sf::Color::Green);
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
        default:
            this->enemy.setFillColor(sf::Color::White);
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
    }

    this->enemies.push_back(this->enemy);
}

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
     * @return void
     * @brief Updates the mouse positions:
     * - Mouse Position Relative to Window (Vector2i)
     */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

/**
 * @brief Updates the enemy spawn timer and spawns enemies
 * @return void
 */
void Game::updateEnemies()
{
    // Updating Timer for Enemy Spawn
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    // Move and update the Enemies
    for (int i = 0; i < this->enemies.size(); i++) 
    {
        bool isDeleted = false;

        this->enemies[i].move(0.f, 2.f);

        // Remove enemies that have passed the bottom of the window
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);

            // Lose health
            this->health -= 1;
            std::cout << "HEALTH:" << this->health << std::endl;
        }
    }

    // ...

    // Check if enemy has been clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;
            bool isDeleted = false;
            for (size_t i = 0; i < this->enemies.size() && isDeleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;

                    std::cout << "POINTS:" << this->points << std::endl;

                    // Delete the enemy
                    isDeleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Game::update()
{
    this->pollEvents();

    if (this->endGame == false)
    {
        this->updateMousePositions();

        this->updateEnemies();
    }

    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

void Game::renderEnemies()
{
    // Render enemies
    for (auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::render()
{
    /**
     * Render Game Objects
     *
     * - Clear old frame
     * - Render objects
     * - Display frame in window
     */
    this->window->clear();

    // Draw game objects
    this->renderEnemies();

    this->window->display();
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}
