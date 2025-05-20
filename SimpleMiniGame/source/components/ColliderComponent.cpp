#include "../../include/components/ColliderComponent.h"
#include "iostream"

ColliderComponent::ColliderComponent(Vector2f Topleft, Vector2f BottomRight) {
    boundingBox.setTopLeft(Topleft);
    boundingBox.setBottomRight(BottomRight);
}

void ColliderComponent::update(Vector2f Topleft, Vector2f BottomRight)
{
    boundingBox.setBottomRight(BottomRight);
    boundingBox.setTopLeft(Topleft);
}


bool ColliderComponent::intersects(const ColliderComponent& other) const {
    return boundingBox.intersects(other.boundingBox);
}


void ColliderComponent::draw(Window* window) {
    window->draw(boundingBox.getDrawableRect());
}


