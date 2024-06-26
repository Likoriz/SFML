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

	bool canJump;
	bool isOnGround;
	bool touchingSensor;
	bool sensors;

	sf::Font font;
	int curHp;
	Medal** activeMedals;
	Medal** allMedals;
	int coins;
	Skills* skills;
public:
	Player(MyDrawable* object);
	void update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	void destruct();
	void ShowInterface(sf::RenderWindow& window);
	void attack(Message m);
	void menu(sf::RenderWindow& window);
	void receiveMedal(int number);
	void receiveSkill();
	void upgrade(int stat);
	void offMedal(int number);
	void onMedal(int number);
	void sendMessage(Message m);
	void checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	
	void setText(sf::Text& text_);
	void setButton(sf::RectangleShape& button, sf::Color color);
	void setCurHP(int hp);
	void setCoins(int c);
	
	bool getObtainedSkill(int skill);
	Medal** getActiveMedals();
	int getCurHP();
	int getCoins();
};

