#pragma once
#include "Layer.h"
#include "MyDrawable.h"

class Level
{
private:
	int width, height, tileWidth, tileHeight;
	int firstTileID;
	sf::Rect<float> drawBounds;
	sf::Texture tilesetImage;
	std::vector<Layer> layers;
public:
	bool loadFromFile(std::string fileName);
	MyDrawable getDrawable(std::string name);
	std::vector<MyDrawable> getDrawables(std::string name);
	//void addDrawable(Drawable object_);
	sf::Vector2i getTileSize();
	void draw(sf::RenderWindow& window);
};

