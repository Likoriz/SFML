#pragma once
#include "Entity.h"
#include "Medal1.h"
#include "Medal2.h"
#include "Medal3.h"
#include "Medal4.h"
#include "Medal5.h"
#include "Medal6.h"
#include "Skills.h"

class Player : public Entity
{
private:
	enum Stat { HP = 0, DAMAGE, DEFENSE };
	enum Skill { CLIMB = 0, DOUBLE, TRIPLE, DASH, WALL };

	sf::Font font;
	
	int curHp;
	Medal** activeMedals;
	Medal** allMedals;
	int coins;
	Skills* skills;
public:
	Player();
	void ShowInterface(sf::RenderWindow& window);
	void destruct();
	void attack();
	void move();
	void menu(sf::RenderWindow& window);
	void receiveMedal(int number);
	void receiveSkill(int skill);
	void upgrade(int stat);
	void setText(sf::Text& text_);
	Medal** getActiveMedals();
	void setButton(sf::RectangleShape& button, sf::Color color);
	void offMedal(int number);
	void onMedal(int number);
};

