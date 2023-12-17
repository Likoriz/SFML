#include <SFML/Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>
#include "Manager.h"
#include "Player.h"

using namespace sf;

int main()
{
	Manager* manager = Manager::getInstance();

	b2Vec2 gravity(0.0f, 1.0f);
	b2World world(gravity);

	Vector2i screenSize(900, 450);

	RenderWindow window;
	window.create(VideoMode(screenSize.x, screenSize.y), "Game");

	View view;
	view.reset(FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
	view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

	window.setVerticalSyncEnabled(true);

	manager->getLevel()->loadFromFile("Map/map.tmx");


	Player player;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::W://jump

					break;
				case Keyboard::D://left

					break;
				case Keyboard::A://right

					break;
				case Keyboard::Escape://menu
					if (manager->getPause() == false)
						manager->setPause(true);
					/*else
						manager->setPause(false);*/
					break;
				}
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)//attack
				{

				}
				else
					if (event.mouseButton.button == Mouse::Right)//shoot
					{

					}
				break;
			}
		}

	world.Step(1.0f / 60.0f, 1, 1);

	//view.setCenter(120 + screenSize.x / 4, 360 + screenSize.y / 4);
	//window.setView(view);

	window.clear(Color::White);

	manager->getLevel()->draw(window);

	if (manager->getPause() == false)
	{
		player.ShowInterface(window);

		for (int i = 0; i < 2; i++)
			if (player.getActiveMedals()[i])
				player.getActiveMedals()[i]->causeEffect();
	}
	else
	{
		player.menu(window);
		manager->setPause(false);
	}

	window.display();
	}

	return 0;
}
