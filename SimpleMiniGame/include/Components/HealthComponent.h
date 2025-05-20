#include <vector>
#include "../graphics/Window.h"
#include "Components.h"

class HealthComponent: public Component
{
protected:
	int currentHealth;
	int maxHealth;

public:
	HealthComponent(int startingHealth, int MaxHealth) 
		: currentHealth(startingHealth), maxHealth{ MaxHealth } {}

	int getHealth() const { return currentHealth; }

	void changeHealth(int amount) {
		currentHealth += amount;
		if (currentHealth > maxHealth) currentHealth = maxHealth;
		if (currentHealth < 0) currentHealth = 0;
	}

	ComponentID getID() const override {
		return ComponentID::HEALTH;
	}

};

