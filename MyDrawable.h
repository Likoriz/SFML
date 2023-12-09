#pragma once
#include "SFML/Graphics.hpp"

class MyDrawable
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
	void setName(std::string name_);
	void setType(std::string type_);
	void setSprite(sf::Sprite sprite_);
	void setRect(sf::Rect<int> rect_);
	void setProperties(std::string propertyName, std::string propertyValue);
};