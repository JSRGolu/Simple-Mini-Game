#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float current = game.getElapsed().asSeconds();
    float elapsedSeconds = current - lastTime;
    int fps = 0;

    game.handleInput();
    game.update(elapsedSeconds);
    game.render(elapsedSeconds);

    float sleepTime = 0;

    if (elapsedSeconds < updateTarget)
    {
        sf::Time sleepDuration = sf::seconds(updateTarget - elapsedSeconds);
        sf::sleep(sleepDuration);
        elapsedSeconds += sleepDuration.asSeconds();
        sleepTime = updateTarget - elapsedSeconds;
    }

    float deltaTime = game.getElapsed().asSeconds() - lastTime;

    if (deltaTime > 0)
        fps = static_cast<int>(1.0f / deltaTime);

    game.setFPS(fps);

    lastTime = current;
}

int main(int argc, char** argv[])
{
    // Try to load the level:
    std::ifstream levelRead{ "levels/lvl0.txt" };
    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    // Convert the read file into a vector of strings, one per line:
    std::vector<std::string> lines;
    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }


    // Create and initalize the game.
    Game game;
    game.init(lines);

    // GAME LOOP (with an update target time at 60FPS)
    float targetFPS = 60.f;
    float updateTarget = 1/targetFPS;
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        //Adaptive loop to elapsed time, with a target update.
        adaptiveLoop(game, lastTime, updateTarget);
    }

    
    return 0;
}