#include "../../include/systems/System.h"
#include "../../include/Components/TTLComponent.h"
#include "iostream"
TTLSystem::TTLSystem()
{
	componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::TTL));
}

void TTLSystem::update(Game* game, Entity* entity, float elapsedTime)
{
	auto ttl = entity->getTTLComponent();
	if (!ttl)
	{
		throw std::runtime_error("TTLSystem: Entity lacks TTLComponent");
	}

	ttl->decreaseTTL();
	std::cout << "[TTLSystem] Entity ID " << entity->getID() << " TTL: " << ttl->getTTL() << std::endl;

	if (ttl->getTTL() <= 0)
	{
		std::cout << "[TTLSystem] >>> DELETING Entity ID " << entity->getID() << std::endl;
		entity->deleteEntity();
	}
}
