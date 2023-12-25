#pragma once
#include "Layer.h"
#include "MyDrawable.h"

class Level
{
private:
	int width, height, tileWidth, tileHeight;
	int firstTileID;
	sf::Texture tilesetImage;
	std::vector<Layer> layers;
public:
	bool loadFromFile(std::string fileName);
	sf::Vector2i getTileSize();
	void draw(sf::RenderWindow& window);
	Level();
};

