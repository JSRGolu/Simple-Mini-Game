#pragma once
#include "Entity.h"
#include "../Components/HealthComponent.h"
#include "../Components/InputComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/PlayerStateComponent.h"
#include "../Observer/AchievementManager.h"
#include "../ObjectPool/FirePool.h"

class Fire;
class VelocityComponent;
class InputComponent;
class PlayerState;

class Player :  public Entity
{
public:
	AchievementManager achievementManager;
	const float playerSpeed = 150.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = 3.f; //in seconds
	const float soundVolume = 50.f;

	Player();
	~Player();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	void onPotionCollision(Player& player, std::shared_ptr<Entity> entity);
	void onLogCollision(Player& player, std::shared_ptr<Entity> entity);

	void handleInput(Game& game);

	bool isAttacking() const { return attacking; }
	void setAttacking(bool at) { attacking = at; }

	bool isShouting() const { return shouting; }
	void setShouting(bool sh) { shouting = sh; }

	int getHealth() const { return healthComponent->getHealth(); }
	

	int getWood() const { return wood; }
	void addWood(int w);

	bool hasSpriteSheet() const { return isSpriteSheet; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	bool collidersWith(Entity& other);

	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }
	std::shared_ptr<VelocityComponent> getVelocity() { return velocity; }
	std::shared_ptr<ColliderComponent> getColliderComponent() override { return collider; }
	std::shared_ptr<PlayerState> getPlayerState() { return playerState; }
	std::shared_ptr<PositionComponent> getPositionComponent() override { return position; }
	std::shared_ptr<PlayerInputComponent> getInputComponent() override { return input; }
	std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocity; }
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() const override { return graphics; }
	std::shared_ptr<LogicComponent> getLogicComponent() const override {
		return std::static_pointer_cast<LogicComponent>(playerState);
	}

private:

	std::shared_ptr<Fire> createFire(FirePool& firePool) ;

	std::shared_ptr<HealthComponent> healthComponent;

	bool attacking;
	bool shouting;
	int health;
	int wood;
	float shootCooldown;
	bool attackSoundPlayed;

	std::shared_ptr<PlayerInputComponent> input;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<ColliderComponent> collider;
	std::shared_ptr<PositionComponent> position;
	std::shared_ptr<PlayerState> playerState;
};

