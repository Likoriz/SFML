#include <SFML/Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>
#include "Manager.h"
#include "Player.h"

using namespace sf;
using namespace std::chrono;

int main()
{
	Manager* manager = Manager::getInstance();

	Vector2i screenSize(900, 450);

	RenderWindow window;
	window.create(VideoMode(screenSize.x, screenSize.y), "JoJo's O Pixel Adventure");

	View view;
	view.reset(FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
	view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

	window.setVerticalSyncEnabled(true);

	manager->getLevel()->loadFromFile("Map/map.tmx");

	Player* player;
	steady_clock::time_point lastTime = steady_clock::now();
	Message M;
	M.target=Manager::getInstance()->getByName("player");
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
					M.type=Move;
					M.ctx.move.speedX=0.0f;
					M.ctx.move.speedY=-15.0f;
					manager->SendMessage(M);
					break;
				case Keyboard::D://left
					
					break;
				case Keyboard::A://right

					break;
				case Keyboard::Escape://menu
					if (manager->getPause() == false)
						manager->setPause(true);
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

		Manager::getInstance()->getWorld()->Step(1.0f / 60.0f, 1, 1);

		//view.setCenter(120 + screenSize.x / 4, 360 + screenSize.y / 4);
		//window.setView(view);
		steady_clock::time_point currentTime = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(currentTime - lastTime);
		
		window.clear(Color::White);

		manager->getLevel()->draw(window);
		player = (Player*)manager->getByName("player");
		
		if (manager->getPause() == false)
		{
			player->ShowInterface(window);

			if (time_span.count() > 10.0)
			{
				lastTime = currentTime;
				for (int i = 0; i < 2; i++)
					if (player->getActiveMedals()[i])
						player->getActiveMedals()[i]->causeEffect();
			}

			//player.move();
		}
		else
		{
			player->menu(window);
			manager->setPause(false);
		}
		manager->sendMSGAll();
		window.display();
	}

	return 0;
}
