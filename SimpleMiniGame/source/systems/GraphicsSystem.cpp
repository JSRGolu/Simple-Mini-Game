#include "../../include/systems/System.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/graphics/Window.h"
#include "../../include/utils/Vector2.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GraphicsSystem::GraphicsSystem() {
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::GRAPHICS));
    componentMask.turnOnBit(static_cast<unsigned int>(ComponentID::POSITION));

}

void GraphicsSystem::update(Game* game, Entity* entity, float elapsedTime)
{
    auto graphicsComp = entity->getGraphicsComponent();
    auto posComp = entity->getPositionComponent();

    if (!graphicsComp || !posComp) throw std::runtime_error("GraphicsSystem: Missing required component");

    sf::Vector2f pos;
    pos.x = posComp->getPosition().x;
    pos.y = posComp->getPosition().y;
    
    graphicsComp->update(elapsedTime, pos);
    graphicsComp->draw(game->getWindow(), pos);
}