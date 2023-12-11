#include "Level.h"
#include <iostream>
#include "SFML\Graphics.hpp"
#include "tinyxml.h"
#include "Manager.h"
using namespace std;
using namespace sf;


bool Level::loadFromFile(string filename)
{
	TiXmlDocument levelFile(filename.c_str());

	if (!levelFile.LoadFile())
	{
		cout << "Failed to load level file: " << filename << endl;
		return false;
	}

	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("heigth"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheigth"));

	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	TiXmlElement* image;
	image = tilesetElement->FirstChildElement("image");
	string imagepath = image->Attribute("source");

	Image img;

	if (!img.loadFromFile(imagepath))
	{
		cout << "Failed to load tilesheet!" << endl;
		return false;
	}

	img.createMaskFromColor(Color(109, 159, 185));
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);

	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	vector<Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			Rect<int> rect;
			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		if (layerElement->Attribute("opacity") != nullptr)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
			layer.setOpacity(255 * opacity);
		}
		else
			layer.setOpacity(255);

		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == nullptr)
			cout << "Layer information isn't found!" << endl;

		TiXmlElement* tileElement;
		tileElement	= layerDataElement->FirstChildElement("tile");

		if (tileElement == nullptr)
		{
			cout << "Tile information isn't found!" << endl;
			return false;
		}

		int x = 0, y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			if (subRectToUse >= 0)
			{
				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(Color(255, 255, 255, layer.getOpacity()));

				layer.addTile(sprite);
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	TiXmlElement* objectGroupElement;

	if (map->FirstChildElement("objectgroup") != nullptr)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				string objectType;
				if (objectElement->Attribute("type") != nullptr)
					objectType = objectElement->Attribute("type");

				string objectName;
				if (objectElement->Attribute("name") != nullptr)
					objectName = objectElement->Attribute("name");

				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != nullptr)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				MyDrawable* object;
				object->setName(objectName);
				object->setType(objectType);
				object->setSprite(sprite);

				Rect<int> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object->setRect(objectRect);

				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");

				if (properties != nullptr)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");

					if (prop != nullptr)
						while (prop)
						{
							string propertyName = prop->Attribute("name");
							string propertyValue = prop->Attribute("value");
							std::map<string, string>tmpProperties = { propertyName, propertyValue };
							object->setProperties(tmpProperties);

							prop = prop->NextSiblingElement("property");
						}
				}

				Manager::getInstance()->addObject(object);
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
		cout << "No object layers found!" << endl;

	return true;
}

void Level::draw(sf::RenderWindow& window)
{
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].getTiles().size(); tile++)
			window.draw(layers[layer].getTile(tile));
}