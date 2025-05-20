#include "../../include/core/Tile.h"
#include <sstream>


void Tile::loadTile(int x, int yy, float sc)
{
	place(x, yy, sc);
}



void Tile::place(int x, int y, float sc)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(static_cast<float>(x) * sc, static_cast<float>(y) * sc);
	sprite.setScale(sc, sc);

	sf::Vector2u textSize = textureData->getTexture().getSize();
	float pixels_x = static_cast<float>(x * (textSize.x * sc));
	float pixels_y = static_cast<float>(y * (textSize.y * sc));
	sprite.setPosition(pixels_x, pixels_y);
}



void Tile::draw(Window* window)
{
	window->draw(sprite);
}
