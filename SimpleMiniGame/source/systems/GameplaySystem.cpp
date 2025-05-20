#include "../../include/systems/System.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/PlayerStateComponent.h"

GameplaySystem::GameplaySystem() {
    componentMask.turnOnBit(static_cast<int>(ComponentID::LOGIC));
}

void GameplaySystem::update(Game* game, Entity* entity, float elapsed) {
    auto logic = entity->getLogicComponent(); 
    if (logic) {
        logic->update(entity, game, elapsed);
    }
}

