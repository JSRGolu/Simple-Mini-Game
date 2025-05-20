#pragma once
#include "../utils/Vector2.h"
#include "../graphics/Window.h"
#include <memory> 
#include "TileTexture.h"

enum class TileType {
	CORRIDOR,
	WALL
};

class Tile
{
private:
	TileType type;
	sf::Vector2i position; 
	std::shared_ptr<TileTexture> textureData; // Flyweight pointer
	sf::Sprite sprite; 

	void place(int x, int y, float sc);

public:
	Tile(TileType tt, std::shared_ptr<TileTexture> texturePtr)
		: position(0, 0), type(tt), textureData(texturePtr)
	{
		sprite.setTexture(textureData->getTexture());
	}

	void loadTile(int x, int yy, float sc);

	inline int x() const { return position.x; }
	inline int y() const { return position.y; }
	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline TileType getType() const { return type; }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }
	void draw(Window* window);
};
