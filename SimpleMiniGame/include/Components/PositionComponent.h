#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class PositionComponent : public Component {

public:
	const Vector2f& getPosition() const { return position; }
	void  setPosition(float x, float y) { position = Vector2f(x, y); }

	ComponentID getID() const override {
		return ComponentID::POSITION;
	}
private:
	Vector2f position;
};
