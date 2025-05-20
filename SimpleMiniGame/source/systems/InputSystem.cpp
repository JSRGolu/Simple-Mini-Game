#include "../../include/systems/System.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/core/Command.h"
#include <iostream>

InputSystem::InputSystem()
{
	componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
}

void InputSystem::update(Game* game, Entity* entity, float elapsedTime)
{
	auto input = entity->getInputComponent();
	auto velocity = entity->getVelocityComponent();

	if (!input || !velocity ) throw std::runtime_error("InputSystem: Missing required component");

	velocity->setVelocity(0.0f, 0.0f);

	auto& commands = input->getCommands(*game);
	for (auto& command : commands)
		command->execute(*game);

	float vx = velocity->getVelocity().x;
	float vy = velocity->getVelocity().y;
	float magnitude = std::sqrt(vx * vx + vy * vy);

	if (magnitude > 0.0f)
		velocity->setVelocity((vx / magnitude), (vy / magnitude));
}