#pragma once
#include "SFML/Graphics.hpp"
class Drawable
{
private:
	std::string name;
	std::string type;
	sf::Rect<int> rect;
	sf::Sprite sprite;
	std::map<std::string, std::string> properties;
public:
	int getPropertyInt(std::string name);
	float getPropertyFloat(std::string name);
	std::string getPropertyString(std::string name);
};

