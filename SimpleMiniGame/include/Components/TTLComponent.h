#pragma once
#include <vector>
#include "../graphics/Window.h"
#include "Components.h"

class TTLComponent : public Component
{
private:
	int ttl;

public:
	TTLComponent(int initialTTL) : ttl(initialTTL) {}

	void decreaseTTL() {
		ttl--;
	}

	int getTTL() const { return ttl; }

	void setTTL(int x) { ttl = x; }

	ComponentID getID() const override {
		return ComponentID::TTL;
	}

};

