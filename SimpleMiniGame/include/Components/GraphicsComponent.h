#pragma once
#include <string>
#include "../graphics/Window.h"
#include "../utils/Vector2.h"
#include <SFML/Graphics.hpp>
#include "Components.h"

class GraphicsComponent: public Component {
public:
    virtual ~GraphicsComponent() = default;

    virtual void init(const std::string& textureFile) = 0;

    virtual void update(float elapsedTime, const sf::Vector2f& position) = 0;

    virtual void draw(Window* window, const sf::Vector2f& position) = 0;

    virtual Vector2f getSize() const = 0;

    virtual void setPosition(const sf::Vector2f& position) = 0;

    ComponentID getID() const override {
        return ComponentID::GRAPHICS;
    }

};
