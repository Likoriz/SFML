#include "Player.h"
#include <iostream>;
#include <SFML/Graphics.hpp>

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

void Player::openMenu()
{

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
