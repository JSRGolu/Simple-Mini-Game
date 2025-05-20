#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/Rectangle.h"
#include "../graphics/Window.h"
#include "../Components/Components.h"

class ColliderComponent : public Component {
private:
    Rectangle boundingBox;

public:
    ColliderComponent(Vector2f Topleft, Vector2f BottomRight);
    void update(Vector2f Topleft, Vector2f BottomRight);
    bool intersects(const ColliderComponent& other) const;
    void draw(Window* window);
    Rectangle getBoundingBox() {
        return boundingBox;
    }
    ComponentID getID() const override {
        return ComponentID::COLLIDER;
    }
};
