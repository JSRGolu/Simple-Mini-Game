#pragma once
#include "../Bitmask/Bitmask.h"
#include "../core/Game.h"
#include "../entities/Entity.h"
#include <memory>

// Forward Declaration
class Game;
class Entity;

class System
{
public:
	virtual ~System() = default;
	virtual void update(Game* game, Entity* entity, float elapsedTime) = 0;

	bool validate(Entity* entity) const
	{
		if (componentMask.getMask() == 0) return false;
		return entity->hasComponent(componentMask);
	}

	const Bitmask getComponentMask() const { return componentMask; }

protected:
	Bitmask componentMask;
};

class TTLSystem : public System
{
public:
	TTLSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};

class InputSystem : public System
{
public:
	InputSystem();
	void update(Game* game, Entity* entity, float elapsedTime) override;
};

class MovementSystem : public System {
public:
	MovementSystem();
	void update(Game* game, Entity* entity, float elapsed) override;
};

class GraphicsSystem : public System {
public:
	GraphicsSystem();
	void update(Game* game, Entity* entity, float elapsed) override;
};

class ColliderSystem : public System {
public:
	ColliderSystem();
	void update(Game* game, Entity* entity, float elapsed) override;
};

class GameplaySystem : public System {
public:
	GameplaySystem();
	void update(Game* game, Entity* entity, float elapsed) override;
};