#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
 * Game Engine
 */
class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    // Mouse Positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    // Game Logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    // Game Objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private Functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Functions
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateEnemies();
    void updateText();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();
};