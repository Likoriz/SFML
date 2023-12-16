#include "Player.h"
#include <iostream>;
#include <SFML/Graphics.hpp>
//#include "Manager.h"

using namespace std;
using namespace sf;

Player::Player()
{
	setHP(100);
	setDMG(20);
	setDEF(100);

	//weaponType = 0;
	coins = 0;
	//state = 0;

	//activeMedals = new Medal();
	skills = new Skills();

	if (!font.loadFromFile("Resources/AmaticSC-Regular.ttf"))
		cout << "Failed to load font!" << endl;
	else
	{
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color::Black);
		text.setStyle(Text::Bold);
	}
}

void Player::ShowInterface(sf::RenderWindow& window)
{
	string hp = to_string(getHP());
	text.setString("HP: " + hp);
	text.setPosition(0, 0);
	window.draw(text);

	string cCoins = to_string(coins);
	text.setString("Coins: " + cCoins);
	text.setPosition(0, 20);
	window.draw(text);
}

void Player::destruct()
{

}

void Player::attack()
{

}

void Player::move()
{

}

void Player::menu(RenderWindow& window)
{
	Texture back;
	back.loadFromFile("Resources/background.jpg");
	Sprite backSprite;
	backSprite.setTexture(back);
	
	RectangleShape bound(Vector2f(window.getSize().x - 200, window.getSize().y - 200));
	bound.setOutlineColor(Color::Black);
	bound.setOutlineThickness(5);
	bound.setPosition(100, 100);
	bound.setFillColor(Color::Transparent);

	text.setString("MeNu");
	text.setPosition(100, 100);

	bool isPaused = true;
	while (isPaused)
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
				case Keyboard::Escape:
					isPaused = false;
					break;
				}
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					text.setString("MeNu");
				}
				else
					if (event.mouseButton.button == Mouse::Right)
					{
						text.setString("mEnU");
					}
				break;
			}
		}

		window.clear(Color::White);
		
		window.draw(backSprite);
		window.draw(bound);
		window.draw(text);

		window.display();
	}
}

void Player::receiveMedal()
{

}

void Player::receiveSkill(int skill)
{
	skills->setSkill(skill);
}

void Player::upgrade(int stat)
{
	if (coins >= 3)
		switch (stat)
		{
		case HP:
			setHP(getHP() + 10);
			break;
		case DAMAGE:
			setDMG(getDMG() + 10);
			break;
		case DEFENSE:
			setDEF(getDEF() + 10);
			break;
		}
}
