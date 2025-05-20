#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

InputHandler::InputHandler()
{
    pauseCommand = std::make_shared<PauseCommand>();
	changeCommand = std::make_shared<ChangeCommand>();
}


std::shared_ptr<Command> InputHandler::handleInput()
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !wasEscapePressed)
    {
        wasEscapePressed = true;  //mark as pressed
        return pauseCommand;  
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !wasChangePressed)
    {
		wasChangePressed = true;  //mark as pressed
        return changeCommand;
    }
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        wasEscapePressed = false;  //when Escape is released, allow next press

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		wasChangePressed = false;  //when F is released, allow next press

    return nullptr;
}

PlayerInputHandler::PlayerInputHandler()
{
    moveRight = std::make_shared<MoveRightCommand>();
    moveLeft = std::make_shared<MoveLeftCommand>();
    moveUp = std::make_shared<MoveUpCommand>();
    moveDown = std::make_shared<MoveDownCommand>();
    attack = std::make_shared<AttackCommand>();
    shout = std::make_shared<ShoutCommand>();
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handlePlayerInput(Game& game)
{
    commands.clear();

    if (game.isChangeCommand())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            commands.push_back(moveUp);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            commands.push_back(moveLeft);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            commands.push_back(moveDown);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            commands.push_back(moveRight);
    }
    
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            commands.push_back(moveUp);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            commands.push_back(moveLeft);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            commands.push_back(moveDown);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            commands.push_back(moveRight);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        commands.push_back(attack);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        commands.push_back(shout);

    return commands;
}