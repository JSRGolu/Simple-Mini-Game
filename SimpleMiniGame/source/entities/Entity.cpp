#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/BitMask/Bitmask.h"
#include <iostream>


Entity::Entity() :
	position(std::make_unique<PositionComponent>()),
	isSpriteSheet(false),
	id(0),
	type(EntityType::UNDEFINED),
	deleted(false)
{}

Entity::Entity(EntityType et) :
	position(std::make_unique<PositionComponent>()),
	isSpriteSheet(false),
	id(0),
	type(et),
	deleted(false)
{}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	//handle by system
}

void Entity::draw(Window* window)
{
	if (graphics)
		graphics->draw(window, sf::Vector2f(getPosition().x, getPosition().y));
}

void Entity::init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc)
{
	graphics = gc;
	graphics->init(textureFile);
	bboxSize = graphics->getSize();
	addComponent(graphics);
	std::cout << "Player init: Graphics component added, Bitmask: " << componentSet.getMask() << std::endl;
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);
	bboxSize = Vector2f(spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x,
					  spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y);
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);

	if(isSpriteSheet)
		spriteSheet.getSprite().setPosition(x, y);
	else
		sprite.setPosition(x, y);
}	

const Vector2f& Entity::getPosition() const
{
	return position->getPosition();
}

const sf::Vector2f& Entity::getSpriteScale() const
{
	if (isSpriteSheet)
	{
		return spriteSheet.getSpriteScale();
	}

	return sprite.getScale();
}

sf::Vector2i Entity::getTextureSize() const
{
	if (isSpriteSheet)
	{
		return spriteSheet.getSpriteSize();
	}

	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

void Entity::addComponent(std::shared_ptr<Component> comp)
{
	componentSet.turnOnBit(static_cast<unsigned int>(comp->getID()));

	std::cout << "Added component ID " << static_cast<unsigned int>(comp->getID())
		<< ", Bitmask: " << componentSet.getMask() << std::endl;
}

bool Entity::hasComponent(Bitmask mask) const
{
	return componentSet.contains(mask);
}
