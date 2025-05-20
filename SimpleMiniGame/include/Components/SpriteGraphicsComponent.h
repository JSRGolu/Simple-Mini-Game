#pragma once
#include "GraphicsComponent.h"
#include "Components.h"
#include "iostream"

class SpriteGraphicsComponent : public GraphicsComponent {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    void init(const std::string& textureFile) override {
        texture.loadFromFile(textureFile);
        sprite.setTexture(texture);
        
        sprite.setScale(1.f, 1.f);
    }

    void update(float elapsedTime, const sf::Vector2f& position) override {
        sprite.setPosition(position);

    }


    void draw(Window* window, const sf::Vector2f& position) override {
        window->draw(sprite);
    }

    Vector2f getSize() const override {
        sf::Vector2u size = texture.getSize();
        sf::Vector2f scale = sprite.getScale();
        return Vector2f(size.x * scale.x, size.y * scale.y);
    }

    
    void setScale(float x, float y) {
        sprite.setScale(x, y);
    }

    sf::Sprite* getSprite() {
        return &sprite;
    }

    const sf::Sprite* getSprite() const {
        return &sprite;
    }

    void setPosition(const sf::Vector2f& position) override {
        sprite.setPosition(position);
    }

    ComponentID getID() const override {
        return ComponentID::GRAPHICS;
    }
};
