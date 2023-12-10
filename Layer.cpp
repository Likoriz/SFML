#include "Layer.h"
using namespace sf;

void Layer::setOpacity(float opacity_)
{
	opacity = opacity_;
}

int Layer::getOpacity()
{
	return opacity;
}

void Layer::addTile(Sprite sprite)
{
	tiles.push_back(sprite);
}

sf::Sprite Layer::getTile(int tile)
{
	return tiles[tile];
}

std::vector<sf::Sprite> Layer::getTiles()
{
	return tiles;
}