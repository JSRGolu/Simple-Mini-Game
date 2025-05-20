#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/SpriteGraphicsComponent.h"
#include "../../include/components/SpriteSheetGraphicsComponent.h"
#include "../../include/audio/SFXAudioManager.h"
#include "../../include/audio/ServiceLocator.h"
#include <iostream>

Game::Game() : paused(false), EntityCounter(0)
{
	inputHandler = std::make_unique<InputHandler>();
	systems.push_back(std::make_shared<TTLSystem>());
	systems.push_back(std::make_shared<InputSystem>());
	systems.push_back(std::make_shared<MovementSystem>());
	systems.push_back(std::make_shared<GraphicsSystem>());
	systems.push_back(std::make_shared<ColliderSystem>());

	audioManager = std::make_unique<SFXAudioManager>();
	ServiceLocator::provide(audioManager.get());
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAtFromPool(std::shared_ptr<T> entity, const std::string& filename, int col, int row, bool isTile, std::shared_ptr<GraphicsComponent> graphics)
{
	if (!entity) return nullptr;
	entity->init(filename, graphics);

	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	if (isTile) {
		entity->setPosition(x, y);
		entity->getPositionComponent()->setPosition(x, y); 
	}
	else {
		entity->setPosition(x + cntrFactor, y + cntrFactor);
		entity->getPositionComponent()->setPosition(x + cntrFactor, y + cntrFactor); 
	}

	return entity;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width,height);

}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			board->loadTileTextures();
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				auto logEntity = logPool.acquire();
				logEntity = buildEntityAtFromPool<Log>(logEntity, "img/log.png", col, row, false, std::make_shared<SpriteGraphicsComponent>());
				addEntity(logEntity);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{
				auto PotionEntity = potionPool.acquire();
				PotionEntity = buildEntityAtFromPool<Potion>(PotionEntity, "img/potion.png", col, row, false, std::make_shared<SpriteGraphicsComponent>());
				addEntity(PotionEntity);
				potionCounter++;
				achievementManager.setTotalPotions(potionCounter);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
			{
				player = std::make_shared<Player>();
				player->init("img/DwarfSpriteSheet_data.txt", std::make_shared<SpriteSheetGraphicsComponent>());
				player->positionSprite(row, col, spriteWH, tileScale);
				addEntity(player);
				std::function<void(Player&, std::shared_ptr<Entity>)> potionCallback = std::bind(&Player::onPotionCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
				std::function<void(Player&, std::shared_ptr<Entity>)> logCallback = std::bind(&Player::onLogCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
				registerCollisionCallback(EntityType::POTION, potionCallback);
				registerCollisionCallback(EntityType::LOG, logCallback);
				std::cout << "playerposition: " << player->getPositionComponent()->getPosition().x << std::endl;
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	EntityCounter++;
	newEntity->setID(EntityCounter);
	entities.push_back(newEntity);
	
	// Add to archetype group based on components
	Bitset archetypeKey = newEntity->getComponentSet().getMask();
	auto& archetype = archetypes[archetypeKey];

	// Resize sparse array
	if (EntityCounter >= archetype.sparse.size()) {
		archetype.sparse.resize(EntityCounter + 1, SIZE_MAX);
	}

	// Add to dense array and update sparse
	archetype.dense.push_back(newEntity);
	archetype.sparse[EntityCounter] = archetype.dense.size() - 1;
}

void Game::handleInput()
{
	std::shared_ptr<Command> command = inputHandler->handleInput();

	if (command)
		command->execute(*this);

	if (player)
		player->handleInput(*this);
}

void Game::registerCollisionCallback(EntityType type, CollisionCallback callback)
{
	collisionCallbacks[type] = callback;
}



void Game::update(float elapsed)
{
	if (!isPaused())
	{
		bigArray(elapsed);

		
		auto it = entities.begin();

		while (it != entities.end()) {
			if (*it) {
				(*it)->update(this, elapsed);
			}
			it++;
		}
		
		entities.erase(
			std::remove_if(entities.begin(), entities.end(),
				[](const std::shared_ptr<Entity>& e) {
					return e->isDeleted();
				}),
			entities.end()
		);
		
		std::shared_ptr<ColliderComponent> playerCollider = player->getColliderComponent();
		if (!playerCollider) return; 

		for (auto& entity : entities) {
			if (entity == player) continue; 

			std::shared_ptr<ColliderComponent> entityCollider = entity->getColliderComponent();
			if (!entityCollider) continue;

			if (playerCollider->intersects(*entityCollider)) {

				EntityType type = entity->getEntityType();
				if (type == EntityType::POTION) {
					achievementManager.onNotify(Event(EventType::PotionCollected));
				}
				auto it = collisionCallbacks.find(type);
				
				if (it != collisionCallbacks.end()) {
					
					it->second(*player, entity);  
				}
				
			}
		}
	}
	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);

	for (auto& archetypePair : archetypes) {
		for (auto& entity : archetypePair.second.dense) {
			std::shared_ptr<ColliderComponent> collider = entity->getColliderComponent();
			collider->draw(&window);
			entity->draw(&window);
		}
	}

	window.drawGUI(*this);
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

std::shared_ptr<Player> Game::getPlayer()
{
	return player;
}

EntityID Game::getIDCounter()
{
	return EntityCounter;
	
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx < entities.size()) {
		return entities[idx];
	}
	return nullptr;
}

void Game::bigArray(float elapsedTime)
{
	cleanArchetypes();

	for (const auto& system : systems) {
		const Bitset systemRequirements = system->getComponentMask().getMask();

		for (auto& archetypePair : archetypes) {
			const Bitset archetypeMask = archetypePair.first;
			auto& archetype = archetypePair.second;

			// Check for match system requirements
			if ((archetypeMask & systemRequirements) == systemRequirements) {
				for (auto& entity : archetype.dense)
				{
					system->update(this, entity.get(), elapsedTime);
				}
			}
		}
	}
}

void Game::cleanArchetypes()
{
	for (auto& archetypePair : archetypes)
	{
		auto& archetype = archetypePair.second;
		size_t i = 0;

		while (i < archetype.dense.size())
		{
			if (archetype.dense[i]->isDeleted())
			{
				EntityID idToRemove = archetype.dense[i]->getID();
				EntityID lastID = archetype.dense.back()->getID();

				// Swap with last element
				std::swap(archetype.dense[i], archetype.dense.back());
				archetype.sparse[lastID] = i;
				archetype.sparse[idToRemove] = SIZE_MAX;

				archetype.dense.pop_back();
			}
			else
			{
				i++;
			}
		}
	}
}
