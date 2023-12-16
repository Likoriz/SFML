#pragma once
#include "Entity.h"
#include "Medal.h"
#include "Skills.h"

class Player : public Entity
{
private:
	enum Stat { HP = 0, DAMAGE, DEFENSE };
	enum Skill { CLIMB = 0, DOUBLE, TRIPLE, DASH, WALL };

	sf::Font font;

	//bool weaponType;
	Medal* activeMedals;
	Medal* collectedMedals;
	int coins;
	Skills* skills;
	//int state;
	//b2FixtureDef fixtureDef;
public:
	Player();
	void ShowInterface(sf::RenderWindow& window);
	void destruct();
	void attack();
	void move();
	void menu(sf::RenderWindow& window);
	void receiveMedal();
	void receiveSkill(int skill);
	void upgrade(int stat);
	void setText(sf::Text& text_);
};

