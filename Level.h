#pragma once
#include "Layer.h"

class Drawable;

class Level
{
private:
	int width, heigth, tileWidth, tileHeigth;
	sf::Rect<float> drawBounds;
	sf::Texture tilesetImage;
	std::vector<Layer> layers;
public:
	bool loadFromFile(std::string fileName);
	Drawable getDrawable(std::string name);
	std::vector<Drawable> getDrawables(std::string name);
	sf::Vector2i getTileSize();
	void draw(sf::RenderWindow& window);
};

