#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../Components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/Components.h"
#include "../../include/BitMask/Bitmask.h"
#include "../Components/TTLComponent.h"
#include "../Components/InputComponent.h"
#include "../Components/VelocityComponent.h"

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3,
	WALL = 4,
};

//forward declaration
class Game;
class PositionComponent;
class Bitmask;
class VelocityComponent;
class LogicComponent;

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc);
	void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	const Vector2f& getPosition() const;
	Rectangle& getBoundingBox() { return boundingBox; };
	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }
	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; }

	virtual std::shared_ptr<ColliderComponent> getColliderComponent() { return nullptr; }
	virtual std::shared_ptr<TTLComponent> getTTLComponent() const { return nullptr; }
	virtual std::shared_ptr<PlayerInputComponent> getInputComponent() { return nullptr; }
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent() { return nullptr; }
	virtual std::shared_ptr<PositionComponent> getPositionComponent() { return nullptr; }
	virtual std::shared_ptr<GraphicsComponent> getGraphicsComponent() const { return nullptr; }
	virtual std::shared_ptr<LogicComponent> getLogicComponent() const { return nullptr; }

	const Bitmask& getComponentSet() const { return componentSet; }
	void addComponent(std::shared_ptr<Component> comp);
	bool hasComponent(Bitmask mask) const;
	Vector2f getBboxSize() {
		return bboxSize;
	}

protected:

	EntityType type;
	EntityID id;
	Bitmask componentSet;

	//Collision
	Rectangle boundingBox;
	Vector2f bboxSize;

	//Graphics-related variables.
	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Texture texture;
	sf::Sprite sprite;

	bool deleted;

	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<GraphicsComponent> graphics;

};