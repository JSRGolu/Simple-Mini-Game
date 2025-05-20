#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/SpriteSheetGraphicsComponent.h"
#include "../../include/components/SpriteGraphicsComponent.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/audio/ServiceLocator.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0), attackSoundPlayed(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
	input = std::make_shared<PlayerInputComponent>();
	addComponent(input);
	healthComponent = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	addComponent(healthComponent);
	velocity = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocity);
	collider = std::make_shared<ColliderComponent>(getPosition(), getPosition() + bboxSize);
	addComponent(collider);
	playerState = std::make_shared<PlayerState>();
	addComponent(playerState);

	std::cout << "Player::init() added position component, current mask: " << getComponentSet().getMask() << std::endl;

}

Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	
	auto spriteSheetGC = std::dynamic_pointer_cast<SpriteSheetGraphicsComponent>(graphics);
	if (spriteSheetGC) {
		auto* sheet = spriteSheetGC->getSpriteSheet();

		if (isAttacking()) {
			sheet->setAnimation("Attack", true, false);
		}
		else if (isShouting()) {
			sheet->setAnimation("Shout", true, false);
		}
		else if (velocity->getVelocity().x > 0) {
			sheet->setAnimation("Walk", true, true);
			sheet->setSpriteDirection(Direction::Right);
		}
		else if (velocity->getVelocity().x < 0) {
			sheet->setAnimation("Walk", true, true);
			sheet->setSpriteDirection(Direction::Left);
		}
		else if (velocity->getVelocity().y != 0) {
			sheet->setAnimation("Walk", true, true);
		}
		else {
			sheet->setAnimation("Idle", true, true);
		}
		if (isAttacking() && !sheet->getCurrentAnim()->isPlaying()) {
			setAttacking(false);
		}
		if (isShouting() && !sheet->getCurrentAnim()->isPlaying()) {
			setShouting(false);
		}

		if (isAttacking()) {
			AnimBase* anim = sheet->getCurrentAnim();
			if (anim && anim->getName() == "Attack" && anim->isInAction()) {
				if (!attackSoundPlayed) {
					ServiceLocator::getAudioManager()->playSound("attack", soundVolume);
					attackSoundPlayed = true;
				}
			}
			else {
				attackSoundPlayed = false;
			}
		}

	}
	
	playerState->update(this, game, elapsed);
	Entity::update(game, elapsed);

	if (shootCooldown > 0) {
		shootCooldown -= elapsed;  
		if (shootCooldown < 0) {
			shootCooldown = 0;  
		}
	}
	
	if (isShouting() && shootCooldown <= 0 && wood >= shootingCost && spriteSheetGC)
	{
		AnimBase* anim = spriteSheetGC->getSpriteSheet()->getCurrentAnim();
		if (anim && anim->isInAction())
		{
			achievementManager.onNotify(Event(EventType::PlayerShouted));
			ServiceLocator::getAudioManager()->playSound("shout", soundVolume);

			auto fire = createFire(game->getFirePool());
			
			game->addEntity(fire);
			wood -= shootingCost;
			shootCooldown = shootCooldownTime;
			std::cout << "shootColldown: " << shootCooldown << std::endl;
		}
	}
}

std::shared_ptr<Fire> Player::createFire(FirePool& firePool)
{
	
	auto fire = firePool.acquire(); 
	std::cout << "[Debug] Fire acquired successfully!" << std::endl;
	
	auto posComp = getPositionComponent();
	Vector2f pos = posComp->getPosition();
	pos.x += getTextureSize().x * 0.5f;
	pos.y += getTextureSize().y * 0.5f;

	fire->setPosition(pos.x, pos.y);

	fire->init("img/fire.png", std::make_shared<SpriteGraphicsComponent>());

	auto fireVel = fire->getVelocityComponent();
	Vector2f vel(1.0f, 0.0f);

	auto gc = std::dynamic_pointer_cast<SpriteSheetGraphicsComponent>(getGraphicsComponent());
	if (gc && gc->getSpriteSheet()->getSpriteDirection() == Direction::Left)
		vel.x = -1.0f;

	fireVel->setVelocity(vel.x * fireSpeed, vel.y * fireSpeed);

	return fire;
}

void Player::handleInput(Game& game)
{
	//handle by system
}

void Player::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}


void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	position->setPosition(x + cntrFactorX, y + cntrFactorY);

	velocity->setVelocity(0.0f, 0.0f);
}


bool Player::collidersWith(Entity& other) {
	auto otherCollider = other.getColliderComponent().get();
	return collider->intersects(*otherCollider);
}


void Player::onPotionCollision(Player& player, std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(entity);
	if (potion) {
		
		potion->deleteEntity();
		player.getHealthComp()->changeHealth(potion->getHealth());
		std::cout << "Collected potion! Restored health to: " << player.getHealth() << std::endl;
		ServiceLocator::getAudioManager()->playSound("pickup", soundVolume);
	}
}

void Player::onLogCollision(Player& player, std::shared_ptr<Entity> entity)
{
	auto log = std::dynamic_pointer_cast<Log>(entity);

	if (log) {
		auto graphics = player.getGraphicsComponent();
		auto spriteSheetGC = std::dynamic_pointer_cast<SpriteSheetGraphicsComponent>(graphics);

		if (spriteSheetGC) {
			AnimBase* anim = spriteSheetGC->getSpriteSheet()->getCurrentAnim();
			if (player.isAttacking() && anim && anim->isInAction()) {
				log->deleteEntity();
				player.addWood(log->getWood());
				std::cout << "Chopped wood! Current wood: " << player.getWood() << std::endl;
			}
		}
	}
}



