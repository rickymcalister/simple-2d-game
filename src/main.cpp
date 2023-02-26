#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game Engine
    Game game;

    // Game Loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    // End of Application
    return 0;
}