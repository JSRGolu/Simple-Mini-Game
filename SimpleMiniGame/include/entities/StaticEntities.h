#pragma once
#include "Entity.h"
#include "../../include/components/ColliderComponent.h"
#include "iostream"

class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION), isInUse(false) {  }
	~Potion() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		collider = std::make_shared<ColliderComponent>(getPosition(), getPosition() + bboxSize);
		addComponent(collider);
		position = std::make_shared<PositionComponent>();
		addComponent(position);
		std::cout << "[Potion] Final PositionComponent: "
			<< position->getPosition().x << ", "
			<< position->getPosition().y << std::endl;

	}
	bool inUse() const
	{
		return isInUse;
	}
	virtual void update(Game* game, float elapsed = 1.0f) override { }

	int getHealth() const { return potionHealth; }

	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }
	std::shared_ptr<PositionComponent> getPositionComponent() override { return position; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() const override { return graphics; }
	void ReverseToggle() { isInUse = !isInUse; }

protected:
	const int potionHealth = 10;
	

private:
	std::shared_ptr<ColliderComponent> collider;
	std::shared_ptr<PositionComponent> position;
	bool isInUse;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG), isInUse(false) {}
	~Log() {}

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override
	{
		Entity::init(textureFile, gc);
		collider = std::make_shared<ColliderComponent>(getPosition(), getPosition() + bboxSize);
		addComponent(collider);
		position = std::make_shared<PositionComponent>();
		addComponent(position);
	}	

	bool inUse() const
	{
		return isInUse;
	}
	virtual void update(Game* game, float elapsed = 1.0f) override {}

	int getWood() const { return woodAdded; }

	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }
	std::shared_ptr<PositionComponent> getPositionComponent() override { return position; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() const override { return graphics; }
	void ReverseToggle() { isInUse = !isInUse; }

protected:
	const int woodAdded = 15;

private:
	std::shared_ptr<ColliderComponent> collider;
	std::shared_ptr<PositionComponent> position;
	bool isInUse;
};

