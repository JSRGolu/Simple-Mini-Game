#pragma once
#include <SFML/Graphics.hpp>

class TileTexture
{
private:
    sf::Texture texture;

public:
    TileTexture() = default;

    bool loadFromFile(const std::string& filename) {
        return texture.loadFromFile(filename);
    }

    const sf::Texture& getTexture() const {
        return texture;
    }
};