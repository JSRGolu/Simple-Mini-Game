#pragma once
#include "../graphics/Window.h"
#include "../core/Board.h"
#include "../entities/Player.h"
#include "../components/GraphicsComponent.h"
#include "../systems/System.h"
#include <unordered_map>
#include "../BitMask/Bitmask.h"
#include "../Observer/AchievementManager.h"
#include <functional>
#include <map>
#include "../ObjectPool/FirePool.h"
#include "../ObjectPool/LogPool.h"
#include "../ObjectPool/PotionPool.h"
#include "../audio/AudioManager.h"

class AudioManager;
class InputHandler;
class System;
using CollisionCallback = std::function<void(Player&, std::shared_ptr<Entity>)>;

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;
	const float globalVolume = 50.f;
	int potionCounter = 0;
	AchievementManager achievementManager;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	void toggleChangeCommand() { changeCommand = !changeCommand; }
	bool isPaused() const { return paused; }
	bool isChangeCommand() const { return changeCommand; }

	std::shared_ptr<Player> getPlayer();

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAtFromPool(std::shared_ptr<T> entity, const std::string& filename, int col, int row, bool isTile, std::shared_ptr<GraphicsComponent> graphics);

	void bigArray(float elapsedTime);
	void registerCollisionCallback(EntityType type, CollisionCallback callback);
	FirePool& getFirePool() { return firePool; }

private:
	FirePool firePool;
	LogPool logPool;
	PotionPool potionPool;
	Window window;
	bool paused;
	bool changeCommand;
	sf::Clock gameClock;
	sf::Time elapsed;
	std::unique_ptr<Board> board;
	std::map<EntityType, CollisionCallback> collisionCallbacks;

	struct ArchetypePacked {
		std::vector<size_t> sparse;
		std::vector<std::shared_ptr<Entity>> dense;
	};

	std::unordered_map<Bitset, ArchetypePacked> archetypes;

	void cleanArchetypes();

	std::vector<std::shared_ptr<Entity>> entities;
	EntityID EntityCounter;
	std::shared_ptr<Player> player;
	std::unique_ptr<InputHandler> inputHandler;
	std::vector<std::shared_ptr<System>> systems;
	std::unique_ptr<AudioManager> audioManager;
};

