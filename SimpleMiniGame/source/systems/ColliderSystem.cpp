#include "../../include/systems/System.h"
#include "../../include/core/Game.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/entities/Entity.h"
#include "iostream"

ColliderSystem::ColliderSystem() {
    componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
    componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
}

void ColliderSystem::update(Game* game, Entity* entity, float elapsed) {
    auto collider = entity->getColliderComponent();
    if (!collider) return;
 
    auto posComp = entity->getPositionComponent();
    Vector2f pos = posComp->getPosition(); 
    Vector2f size = entity->getBboxSize();

    collider->update(pos, pos + size);
    collider->draw(game->getWindow());
   
}

