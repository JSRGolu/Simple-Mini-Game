#include "../../include/core/Board.h"
#include <stdexcept>
#include <iostream>

using const_reference = std::vector<Tile*>::const_reference;
using reference = std::vector<Tile*>::reference;

Board::Board(size_t newWidth, size_t newHeight)
	: width(newWidth), height(newHeight), grid(newWidth* newHeight, nullptr)
{
}


Board::~Board()
{
	for (Tile* t : grid)
	{
		delete t;
	}
	grid.clear();
}


reference Board::get(int x, int y)
{
	auto pos = y * static_cast<int>(width) + x;
	if (pos >= static_cast<int>(grid.size()) || pos < 0)
	{
		throw std::runtime_error("Out of bounds of the board.");
	}

	return grid[static_cast<size_t>(y * static_cast<int>(width) + x)];
}

const_reference Board::get(int x, int y) const
{
	auto pos = y * static_cast<int>(width) + x;
	if (pos > static_cast<int>(grid.size()) || pos < 0)
	{
		throw std::runtime_error("Out of bounds of the board.");
	}

	return grid[static_cast<size_t>(y * static_cast<int>(width) + x)];
}

void Board::loadTileTextures()
{
	auto corridorTexture = std::make_shared<TileTexture>();
	corridorTexture->loadFromFile("img/floor.png");
	tileTextures[TileType::CORRIDOR] = corridorTexture;

	auto wallTexture = std::make_shared<TileTexture>();
	wallTexture->loadFromFile("img/wall.png");
	tileTextures[TileType::WALL] = wallTexture;

}


void Board::addTile(int x, int y, float scale, TileType tt, const std::string& filename)
{
	if (!inBounds(x, y))
		throw std::runtime_error("Out of bounds of the board.");

	std::shared_ptr<TileTexture> texturePtr = getTileTexture(tt);

	Tile* newTile = new Tile(tt, texturePtr); 
	newTile->loadTile(x, y, scale);

	grid[y * width + x] = newTile;

}



void Board::draw(Window* wnd)
{
	for (int i = 0; i < static_cast<int>(height); i++)
	{
		for (int j = 0; j < static_cast<int>(width); ++j)
		{
			get(j, i)->draw(wnd);
		}
	}
}

std::shared_ptr<TileTexture> Board::getTileTexture(TileType type)
{
	return tileTextures.at(type);
}


void Board::print()
{
	for (int i = 0; i < static_cast<int>(height); i++)
	{
		for (int j = 0; j < static_cast<int>(width); ++j)
		{
			char c = get(j, i)->getType() == TileType::CORRIDOR ? '.' : 'w';
			std::cout << " " << c;
		

		}
		std::cout << "\n";
	}
}