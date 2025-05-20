#pragma once
#include "Entity.h"
#include "../Components/TTLComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/GraphicsComponent.h"
#include "../Components/SpriteGraphicsComponent.h"
#include "../Components/ColliderComponent.h"

class Fire : public Entity
{
public:
	 int startTimeToLive = 0; // frames

	Fire();
	~Fire();

	void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override;
	virtual void update(Game* game, float elapsed = 1.0f) override;
	void setTTL(int x) { startTimeToLive = x; }
	bool inUse() const { return startTimeToLive > 0; }
	int getTTL() const { return ttl->getTTL(); }
	std::shared_ptr<TTLComponent> getTTLComponent() const override { return ttl; }
	std::shared_ptr<PositionComponent> getPositionComponent() override { return position; }
	std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocity; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() const override { return graphics; }
	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }

private:
	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;
	std::shared_ptr<ColliderComponent> collider;
};
