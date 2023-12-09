#pragma once
#include "SFML/Graphics.hpp"

class Layer
{
private:
	int opacity;
	std::vector<sf::Sprite> tiles;
public:
	void setOpacity(float opacity_);
	int getOpacity();
	void addTile(sf::Sprite sprite);
};

