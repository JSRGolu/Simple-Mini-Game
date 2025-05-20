#include "../../include/systems/System.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/utils/Vector2.h"
#include <iostream>

MovementSystem::MovementSystem()
{
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::VELOCITY));
}

void MovementSystem::update(Game* game, Entity* entity, float elapsed)
{
    auto posComp = entity->getPositionComponent();
    auto velComp = entity->getVelocityComponent();

    if (!posComp || !velComp) throw std::runtime_error("MovementSystem: Missing required component");
    
    Vector2f currentPos = posComp->getPosition();
    Vector2f velocity = velComp->getVelocity();
    float speed = velComp->getSpeed();
    currentPos.x += velocity.x * speed * elapsed;
    currentPos.y += velocity.y * speed * elapsed;
    posComp->setPosition(currentPos.x, currentPos.y);

}