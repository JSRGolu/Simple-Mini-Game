#pragma once
#include <memory>
#include "Components.h"
#include "../core/Command.h"
#include <vector>

// Forward declaration
class Game;
class PlayerInputHandler;
class Command;

class InputComponent:public Component {

public:
	virtual ~InputComponent() = default;
	virtual void Update(Game& game) = 0;
};

class PlayerInputComponent : public InputComponent {

public:
	PlayerInputComponent();
	void Update(Game& game) override;
	std::vector<std::shared_ptr<Command>>& getCommands(Game& game);
	ComponentID getID() const override {
		return ComponentID::INPUT;
	}

private:
	std::unique_ptr<PlayerInputHandler> inputHandler;
	std::vector<std::shared_ptr<Command>> commands;
};