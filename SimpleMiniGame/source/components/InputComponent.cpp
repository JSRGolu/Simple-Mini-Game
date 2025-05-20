#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"

PlayerInputComponent::PlayerInputComponent()
{
	inputHandler = std::make_unique<PlayerInputHandler>();
}

void PlayerInputComponent::Update(Game& game)
{
	auto v = game.getPlayer()->getVelocity();
	v->setVelocity(0.0f, 0.0f);

	auto& commands = inputHandler->handlePlayerInput(game);

	for (auto& command : commands)
		command->execute(game);
}

std::vector<std::shared_ptr<Command>>& PlayerInputComponent::getCommands(Game& game) {
    commands = inputHandler->handlePlayerInput(game);
    return commands;
}