#pragma once
#include "GraphicsComponent.h"
#include "../graphics/SpriteSheet.h"
#include "Components.h"


class SpriteSheetGraphicsComponent : public GraphicsComponent {
private:
    SpriteSheet spriteSheet;

public:
    void init(const std::string& textureFile) override {
        spriteSheet.loadSheet(textureFile);
        spriteSheet.setAnimation("Idle", true, true);
    }

    void update(float elapsedTime, const sf::Vector2f& position) override {
        spriteSheet.getSprite().setPosition(position);
        spriteSheet.update(elapsedTime);
    }


    void draw(Window* window, const sf::Vector2f& position) override {
        sf::Sprite* sp = &spriteSheet.getSprite();
        const sf::Vector2f pos = sp->getPosition();
        window->draw(spriteSheet.getSprite());
    }

    Vector2f getSize() const override {
        auto size = spriteSheet.getSpriteSize();
        auto scale = spriteSheet.getSpriteScale();
        return Vector2f(size.x * scale.x, size.y * scale.y);
    }

    SpriteSheet* getSpriteSheet() {
        return &spriteSheet;
    }

    const SpriteSheet* getSpriteSheet() const {
        return &spriteSheet;
    }

    void setPosition(const sf::Vector2f& position) override {
        spriteSheet.getSprite().setPosition(position);
    }

    ComponentID getID() const override {
        return ComponentID::GRAPHICS;
    }

};
