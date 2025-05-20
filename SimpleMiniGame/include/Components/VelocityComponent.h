#pragma once
#include "../utils/Vector2.h"
#include "../entities/Entity.h"
#include "Components.h"

// Forward declaration
class Entity;

class VelocityComponent : public Component {

public:
	VelocityComponent(float speed = 1.0f) : speed(speed) {}

	void setVelocity(float x, float y) { velocity = Vector2f(x, y); }
	const Vector2f& getVelocity() const { return velocity; }
	float getSpeed() const { return speed; }

	ComponentID getID() const override {
		return ComponentID::VELOCITY;
	}

private:
	Vector2f velocity;
	float speed;

};