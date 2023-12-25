#include <SFML/Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>
#include "Manager.h"
#include "Player.h"

using namespace sf;
using namespace std;
using namespace std::chrono;

int main()
{
	Manager* manager = Manager::getInstance();

	Vector2i screenSize(900, 450);

	RenderWindow window;
	window.create(VideoMode(screenSize.x, screenSize.y), "JoJo's Omnipotent Pixel Adventure");

	View view;
	view.reset(FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
	view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

	window.setVerticalSyncEnabled(true);

	manager->getLevel()->loadFromFile("Map/map.tmx");

	Player* player;

	steady_clock::time_point lastTime = steady_clock::now();
	steady_clock::time_point lastDmg = steady_clock::now();

	Message M;
	M.target = manager->getByName("player");
	while (window.isOpen())
	{
		player = (Player*)manager->getByName("player");
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
					if (player->getObject()->getBody()->GetLinearVelocity().y == 0)
					{
						M.type = Move;
						if (player->getObject()->getBody()->GetLinearVelocity().x == 0)
						{
							M.ctx.move.speedX = 0.0f;
							M.ctx.move.speedY = -100.0f;
						}
						else
							M.ctx.move.speedY = -100.0f;
						manager->SendMessage(M);
					}
					break;
				case Keyboard::D://left
					M.type = Move;
					if (player->getObject()->getBody()->GetLinearVelocity().y <= 0)
					{
						M.ctx.move.speedX = 70.0f;
						M.ctx.move.speedY = 0.0f;
					}
					else
						M.ctx.move.speedX = 70.0f;
					manager->SendMessage(M);
					break;
				case Keyboard::A://right
					M.type = Move;
					if (player->getObject()->getBody()->GetLinearVelocity().y <= 0)
					{
						M.ctx.move.speedX = -70.0f;
						M.ctx.move.speedY = 0.0f;
					}
					else
						M.ctx.move.speedX = -70.0f;
					manager->SendMessage(M);
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
					Vector2f mouseCoords = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				}
				else
					if (event.mouseButton.button == Mouse::Right)//shoot
					{

					}
				break;
			}
		}

		manager->getWorld()->Step(1.0f / 60.0f, 6, 2);

		steady_clock::time_point currentTime = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(currentTime - lastTime);
		duration<double> timeDmg = duration_cast<duration<double>>(currentTime - lastDmg);

		window.clear(Color::White);

		manager->getLevel()->draw(window);

		if (manager->getPause() == false)
		{
			player->ShowInterface(window);

			if (time_span.count() > 5.0)
			{
				lastTime = currentTime;
				for (int i = 0; i < 2; i++)
					if (player->getActiveMedals()[i])
						player->getActiveMedals()[i]->causeEffect();
			}
			player->move();
			player->checkCollision(timeDmg, lastDmg, currentTime);
		}
		else
		{
			player->menu(window);
			manager->setPause(false);
		}
		manager->sendMSGAll();
		manager->updateAll();

		window.display();
	}

	return 0;
}