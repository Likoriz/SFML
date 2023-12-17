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
	coins = 10;
	//state = 0;

	activeMedals = new Medal * [2];
	for (int i = 0; i < 2; i++)
		activeMedals[i] = nullptr;

	allMedals = new Medal * [8];
	allMedals[0] = new Medal1();
	allMedals[1] = new Medal2();
	allMedals[2] = new Medal3();
	allMedals[3] = new Medal4();
	allMedals[4] = new Medal5();
	allMedals[5] = new Medal6();
	allMedals[6] = new Medal7();
	allMedals[7] = new Medal8();

	skills = new Skills();

	if (!font.loadFromFile("Resources/AmaticSC-Regular.ttf"))
		cout << "Failed to load font!" << endl;
}

void Player::ShowInterface(sf::RenderWindow& window)
{
	Text text;
	setText(text);

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

void Player::setText(sf::Text& text_)
{
	text_.setFont(font);
	text_.setCharacterSize(24);
	text_.setFillColor(Color::Black);
	text_.setStyle(Text::Bold);
}

void Player::menu(RenderWindow& window)
{
	Texture back;
	back.loadFromFile("Resources/background.jpg");
	Sprite backSprite;
	backSprite.setTexture(back);

	RectangleShape bound;
	bound.setSize(Vector2f(700, 250));
	//bound.setSize(Vector2f(window.getSize().x - 200, window.getSize().y - 200));
	bound.setOutlineColor(Color::Black);
	bound.setOutlineThickness(5);
	bound.setPosition(100, 100);
	bound.setFillColor(Color::Transparent);

	Text text, textHp, textCoins, textDmg, textDef;
	string cCoins, hp, dmg, def;

	text.setString("MENU");

	setText(text);
	setText(textCoins);
	setText(textHp);
	setText(textDmg);
	setText(textDef);

	text.setPosition(110, 110);
	textCoins.setPosition(110, 150);
	textHp.setPosition(110, 170);
	textDmg.setPosition(110, 190);
	textDef.setPosition(110, 210);

	RectangleShape buttonHp;
	buttonHp.setSize(Vector2f(20, 20));
	buttonHp.setPosition(200, 175);
	buttonHp.setOutlineColor(Color::Black);
	buttonHp.setOutlineThickness(1);
	buttonHp.setFillColor(Color::Green);

	RectangleShape buttonDmg;
	buttonDmg.setSize(Vector2f(20, 20));
	buttonDmg.setPosition(200, 195);
	buttonDmg.setOutlineColor(Color::Black);
	buttonDmg.setOutlineThickness(1);
	buttonDmg.setFillColor(Color::Green);

	RectangleShape buttonDef;
	buttonDef.setSize(Vector2f(20, 20));
	buttonDef.setPosition(200, 215);
	buttonDef.setOutlineColor(Color::Black);
	buttonDef.setOutlineThickness(1);
	buttonDef.setFillColor(Color::Green);

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
				Vector2f mouseCoords = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (event.mouseButton.button == Mouse::Left && buttonHp.getGlobalBounds().contains(mouseCoords))
					upgrade(HP);
				else
					if (event.mouseButton.button == Mouse::Left && buttonDmg.getGlobalBounds().contains(mouseCoords))
						upgrade(DAMAGE);
					else
						if (event.mouseButton.button == Mouse::Left && buttonDef.getGlobalBounds().contains(mouseCoords))
							upgrade(DEFENSE);
				break;
			}
		}

		if (coins >= 2)
		{
			buttonHp.setFillColor(Color::Green);
			buttonDmg.setFillColor(Color::Green);
			buttonDef.setFillColor(Color::Green);
		}
		else
		{
			buttonHp.setFillColor(Color::Red);
			buttonDmg.setFillColor(Color::Red);
			buttonDef.setFillColor(Color::Red);
		}

		cCoins = to_string(coins);
		textCoins.setString("Coins: " + cCoins);

		hp = to_string(getHP());
		textHp.setString("HP: " + hp);

		dmg = to_string(getDMG());
		textDmg.setString("DMG: " + dmg);

		def = to_string(getDEF());
		textDef.setString("DEF: " + def);

		window.clear(Color::White);

		window.draw(backSprite);
		window.draw(bound);

		window.draw(text);
		window.draw(textCoins);
		window.draw(textHp);
		window.draw(textDmg);
		window.draw(textDef);

		window.draw(buttonHp);
		window.draw(buttonDmg);
		window.draw(buttonDef);

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
	if (coins >= 2)
	{
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

		coins -= 2;
	}
}
