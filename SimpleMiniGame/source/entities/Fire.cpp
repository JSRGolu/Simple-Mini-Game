#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "iostream"


Fire::Fire() : Entity(EntityType::FIRE) {}
Fire::~Fire() {}

void Fire::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	
	Entity::init(textureFile, gc);
	graphics = gc;
	addComponent(graphics);


	ttl = std::make_shared<TTLComponent>(startTimeToLive);
	addComponent(ttl);
	std::cout << " ttl::" <<  ttl->getTTL() << std::endl;


	velocity = std::make_shared<VelocityComponent>();
	addComponent(velocity);

	
	position = std::make_shared<PositionComponent>();
	Vector2f pos = getPosition();
	position->setPosition(pos.x, pos.y);
	addComponent(position);

	
	collider = std::make_shared<ColliderComponent>(getPosition(), getPosition() + getGraphicsComponent()->getSize());
	addComponent(collider);
}

void Fire::update(Game* game, float elapsed)
{
	//handle by system
}
