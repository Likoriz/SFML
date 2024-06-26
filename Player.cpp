#include "Player.h"
#include <iostream>;
#include <SFML/Graphics.hpp>

using namespace std::chrono;
using namespace std;
using namespace sf;

void Player::destruct()
{
	delete[] activeMedals;

	for (int i = 0; i < 6; i++)
		delete[] allMedals[i];
	delete allMedals;

	delete skills;
}

void Player::attack(Message m)
{
	if (m.type == DealDmg)
	{
		b2Body* body = getObject()->getBody();
		b2Vec2 center = body->GetPosition();
		int r = getRadius();

		vector<GameObject*>* gameObjects = Manager::getInstance()->getGame();

		for (auto x : *gameObjects)
		{
			b2Body* enemy = x->getObject()->getBody();
			if (enemy != body)
			{
				b2Vec2 bodyPosition = enemy->GetPosition();
				float distance = (bodyPosition - center).Length();

				string name = x->getDrawable()->getName();
				if (name == "walking" || name == "hiding")
					if (distance <= r)
					{
						m.type = DealDmg;
						m.target = x;
						m.ctx.dealDmg.dmg = getDMG();
						Manager::getInstance()->SendMessage(m);
					}
			}
		}
	}
	else if (m.type == Create)
	{

	}
}

Player::Player(MyDrawable* object)
{
	setHP(100);
	setDMG(20);
	setDEF(10);
	setRadius(50);

	canJump = false;
	isOnGround = true;

	coins = 0;
	curHp = getHP();

	activeMedals = new Medal * [2];
	for (int i = 0; i < 2; i++)
		activeMedals[i] = nullptr;

	allMedals = new Medal * [6];
	allMedals[0] = new Medal1();
	allMedals[1] = new Medal2();
	allMedals[2] = new Medal3();
	allMedals[3] = new Medal4();
	allMedals[4] = new Medal5();
	allMedals[5] = new Medal6();

	receiveMedal(0);


	skills = new Skills();

	if (!font.loadFromFile("Resources/AmaticSC-Regular.ttf"))
		cout << "Failed to load font!" << endl;

	setDrawable(object);
	Rect<int> rect = object->getRect();
	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_dynamicBody, rect.left, rect.top - tileSize.y, rect, true, 1.0, 1.0));
}

void Player::sendMessage(Message m)
{
	switch (m.type)
	{
	case Move:
	{
		b2Body* playerBody = getObject()->getBody();

		b2Vec2 speed;
		speed = { m.ctx.move.speedX, m.ctx.move.speedY };

		playerBody->SetLinearVelocity(speed);
		break;
	}
	case DealDmg:
	{
		if (getInvincibility() == false && m.ctx.dealDmg.dmg > 0)
			curHp -= max((int)(m.ctx.dealDmg.dmg - getDEF()), 1);
		else if (m.ctx.dealDmg.dmg < 0)
			curHp -= m.ctx.dealDmg.dmg;

		if (curHp > getHP())
			curHp = getHP();
		else if (curHp < 1)
		{
			Message M;
			M.type = Erase;
			M.ctx.erase.objectToDelete = this;
			Manager::getInstance()->SendMessage(M);
			cout << "The player is dead!";
			exit(0);
		}
		break;
	}
	case Jump:
	{
		if (isOnGround)
		{
			isOnGround = false;
			touchingSensor = false;
			auto vel = getObject()->getBody()->GetLinearVelocity();
			vel.y = -100.0f;
			getObject()->getBody()->SetLinearVelocity(vel);
		}
		else
			if (getObtainedSkill(TRIPLE) && canJump)
			{
				canJump = false;
				touchingSensor = false;
				auto vel = getObject()->getBody()->GetLinearVelocity();
				vel.y = -100.0f;
				getObject()->getBody()->SetLinearVelocity(vel);
			}

		b2Body* mybody = getObject()->getBody();
		for (b2ContactEdge* edge = mybody->GetContactList(); edge; edge = edge->next)
		{
			b2Contact* contact = edge->contact;

			if (contact->GetFixtureA()->IsSensor() && contact->GetFixtureA()->GetBody() == mybody ||
				contact->GetFixtureB()->IsSensor() && contact->GetFixtureB()->GetBody() == mybody)
			{
				touchingSensor = true;
				break;
			}
		}

		if (touchingSensor)
		{
			isOnGround = true;
			canJump = true;
		}
	}
	}
}

void Player::update(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::D))
	{
		auto vel = getObject()->getBody()->GetLinearVelocity();
		vel.x = 70.0f;
		getObject()->getBody()->SetLinearVelocity(vel);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::A))
	{
		auto vel = getObject()->getBody()->GetLinearVelocity();
		vel.x = -70.0f;
		getObject()->getBody()->SetLinearVelocity(vel);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::LShift) && getObtainedSkill(DASH))
		if (time_span.count() > 3.0)
		{
			last_time = current_time;
			auto vel = getObject()->getBody()->GetLinearVelocity();
			vel.x *= 5.0f;
			getObject()->getBody()->SetLinearVelocity(vel);
		}

	if (time_span.count() > 5.0)
	{
		if (Manager::getInstance()->getPause() == false)
		{
			last_time = current_time;
			for (int i = 0; i < 2; i++)
				if (getActiveMedals()[i])
					getActiveMedals()[i]->causeEffect();
		}
	}

	if (getActiveMedals()[0])
	{
		if (getActiveMedals()[0]->getName() == "Two Ends")
			getActiveMedals()[0]->causeEffect();
	}
	else if (getActiveMedals()[1])
		if (getActiveMedals()[1]->getName() == "Two Ends")
			getActiveMedals()[1]->causeEffect();

	move();
	checkCollision(time_span, last_time, current_time);
}

void Player::menu(RenderWindow& window)
{
	Texture back;
	back.loadFromFile("Resources/background.jpg");
	Sprite backSprite;
	backSprite.setTexture(back);

	RectangleShape bound;
	bound.setSize(Vector2f(700, 250));
	bound.setOutlineColor(Color::Black);
	bound.setOutlineThickness(5);
	bound.setFillColor(Color::Transparent);
	bound.setPosition(100, 100);

#pragma region BASICS
	Text text, textHp, textCoins, textDmg, textDef;
	string cCoins, hp, dmg, def;

	text.setString("STATUS");

	setText(text); setText(textCoins); setText(textHp); setText(textDmg); setText(textDef);

	text.setPosition(110, 110);
	textCoins.setPosition(110, 150);
	textHp.setPosition(110, 170);
	textDmg.setPosition(110, 190);
	textDef.setPosition(110, 210);

	RectangleShape buttonHp;
	buttonHp.setSize(Vector2f(20, 20));
	buttonHp.setPosition(200, 175);
	setButton(buttonHp, Color::Green);

	RectangleShape buttonDmg;
	buttonDmg.setSize(Vector2f(20, 20));
	buttonDmg.setPosition(200, 195);
	setButton(buttonDmg, Color::Green);

	RectangleShape buttonDef;
	buttonDef.setSize(Vector2f(20, 20));
	buttonDef.setPosition(200, 215);
	setButton(buttonDef, Color::Green);
#pragma endregion BASICS

#pragma region SKILLS
	Text textSkills, textClimb, textDouble, textTriple, textDash;
	string abClimb, abDouble, abTriple, abDash;

	setText(textSkills); setText(textClimb); setText(textDouble); setText(textTriple); setText(textDash);

	textSkills.setPosition(250, 110);
	textClimb.setPosition(250, 150);
	textDouble.setPosition(250, 170);
	textTriple.setPosition(250, 190);
	textDash.setPosition(250, 210);

	if (skills->getSkill(CLIMB))
		abClimb = "YES";
	else
		abClimb = "NO";

	if (skills->getSkill(DOUBLE))
		abDouble = "YES";
	else
		abDouble = "NO";

	if (skills->getSkill(TRIPLE))
		abTriple = "YES";
	else
		abTriple = "NO";

	if (skills->getSkill(DASH))
		abDash = "YES";
	else
		abDash = "NO";

	textSkills.setString("SKILLS");
	textClimb.setString("Climbing: " + abClimb);
	textDouble.setString("Double Jumping: " + abDouble);
	textTriple.setString("Triple Jumping: " + abTriple);
	textDash.setString("Dashing: " + abDash);
#pragma endregion SKILLS

#pragma region MEDALS
	Text textMedals;
	Text textA1, textA2;
	Text text1, text2, text3, text4, text5, text6;

	setText(textMedals);
	setText(textA1); setText(textA2);
	setText(text1); setText(text2); setText(text3); setText(text4); setText(text5); setText(text6);

	textMedals.setString("ACTIVE MEDALS");

	textMedals.setPosition(500, 110);
	textA1.setPosition(500, 150);
	textA2.setPosition(500, 170);
	text1.setPosition(500, 210);
	text2.setPosition(500, 230);
	text3.setPosition(500, 250);
	text4.setPosition(500, 270);
	text5.setPosition(500, 290);
	text6.setPosition(500, 310);

	RectangleShape buttonA1;
	buttonA1.setSize(Vector2f(20, 20));
	buttonA1.setPosition(700, 155);
	setButton(buttonA1, Color::Red);

	RectangleShape buttonA2;
	buttonA2.setSize(Vector2f(20, 20));
	buttonA2.setPosition(700, 175);
	setButton(buttonA2, Color::Red);

	RectangleShape button1;
	button1.setSize(Vector2f(20, 20));
	button1.setPosition(700, 215);
	setButton(button1, Color::Green);

	RectangleShape button2;
	button2.setSize(Vector2f(20, 20));
	button2.setPosition(700, 235);
	setButton(button2, Color::Green);

	RectangleShape button3;
	button3.setSize(Vector2f(20, 20));
	button3.setPosition(700, 255);
	setButton(button3, Color::Green);

	RectangleShape button4;
	button4.setSize(Vector2f(20, 20));
	button4.setPosition(700, 275);
	setButton(button4, Color::Green);

	RectangleShape button5;
	button5.setSize(Vector2f(20, 20));
	button5.setPosition(700, 295);
	setButton(button5, Color::Green);

	RectangleShape button6;
	button6.setSize(Vector2f(20, 20));
	button6.setPosition(700, 315);
	setButton(button6, Color::Green);
#pragma endregion MEDALS

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
				if (event.mouseButton.button == Mouse::Left)
					if (buttonHp.getGlobalBounds().contains(mouseCoords))
						upgrade(HP);
					else if (buttonDmg.getGlobalBounds().contains(mouseCoords))
						upgrade(DAMAGE);
					else if (buttonDef.getGlobalBounds().contains(mouseCoords))
						upgrade(DEFENSE);
					else if (buttonA1.getGlobalBounds().contains(mouseCoords))
						offMedal(0);
					else if (buttonA2.getGlobalBounds().contains(mouseCoords))
						offMedal(1);
					else if (button1.getGlobalBounds().contains(mouseCoords))
						onMedal(0);
					else if (button2.getGlobalBounds().contains(mouseCoords))
						onMedal(1);
					else if (button3.getGlobalBounds().contains(mouseCoords))
						onMedal(2);
					else if (button4.getGlobalBounds().contains(mouseCoords))
						onMedal(3);
					else if (button5.getGlobalBounds().contains(mouseCoords))
						onMedal(4);
					else if (button6.getGlobalBounds().contains(mouseCoords))
						onMedal(5);
				break;
			}
		}

#pragma region UPDATEBASICS
		cCoins = to_string(coins);
		textCoins.setString("Coins: " + cCoins);

		hp = to_string(curHp);
		string maxhp = to_string(getHP());
		textHp.setString("HP: " + hp + "/" + maxhp);

		dmg = to_string(getDMG());
		textDmg.setString("DMG: " + dmg);

		def = to_string(getDEF());
		textDef.setString("DEF: " + def);
#pragma endregion UPDATEBASICS

#pragma region UPDATEMEDALS
		if (activeMedals[0])
			textA1.setString(activeMedals[0]->getName());
		else
			textA1.setString("None");

		if (activeMedals[1])
			textA2.setString(activeMedals[1]->getName());
		else
			textA2.setString("None");

		if (allMedals[0]->getCollected())
			text1.setString(allMedals[0]->getName());
		else
			text1.setString("None");

		if (allMedals[1]->getCollected())
			text2.setString(allMedals[1]->getName());
		else
			text2.setString("None");

		if (allMedals[2]->getCollected())
			text3.setString(allMedals[2]->getName());
		else
			text3.setString("None");

		if (allMedals[3]->getCollected())
			text4.setString(allMedals[3]->getName());
		else
			text4.setString("None");

		if (allMedals[4]->getCollected())
			text5.setString(allMedals[4]->getName());
		else
			text5.setString("None");

		if (allMedals[5]->getCollected())
			text6.setString(allMedals[5]->getName());
		else
			text6.setString("None");
#pragma endregion UPDATEMEDALS

		window.clear(Color::White);

		window.draw(backSprite);
		window.draw(bound);

#pragma region DRAWBASICS
		window.draw(text); window.draw(textCoins); window.draw(textHp); window.draw(textDmg); window.draw(textDef);

		if (coins >= 2)
		{
			window.draw(buttonHp); window.draw(buttonDmg); window.draw(buttonDef);
		}
#pragma endregion DRAWBASICS

#pragma region DRAWSKILLS
		window.draw(textSkills); window.draw(textClimb); window.draw(textDouble); window.draw(textTriple); window.draw(textDash);
#pragma endregion DRAWSKILLS

#pragma region DRAWMEDALS
		window.draw(textMedals); window.draw(textA1); window.draw(textA2);

		window.draw(text1); window.draw(text2); window.draw(text3); window.draw(text4); window.draw(text5); window.draw(text6);

		if (activeMedals[0])
			window.draw(buttonA1);
		if (activeMedals[1])
			window.draw(buttonA2);

		if (allMedals[0]->getCollected())
			window.draw(button1);
		if (allMedals[1]->getCollected())
			window.draw(button2);
		if (allMedals[2]->getCollected())
			window.draw(button3);
		if (allMedals[3]->getCollected())
			window.draw(button4);
		if (allMedals[4]->getCollected())
			window.draw(button5);
		if (allMedals[5]->getCollected())
			window.draw(button6);
#pragma endregion DRAWMEDALS

		window.display();
	}
}

void Player::setButton(RectangleShape& button, Color color)
{
	button.setOutlineColor(Color::Black);
	button.setOutlineThickness(1);
	button.setFillColor(color);
}

void Player::ShowInterface(sf::RenderWindow& window)
{
	Text text;
	setText(text);

	string hp = to_string(curHp);
	string maxhp = to_string(getHP());
	text.setString("HP: " + hp + "/" + maxhp);
	text.setPosition(0, 0);
	window.draw(text);

	string cCoins = to_string(coins);
	text.setString("Coins: " + cCoins);
	text.setPosition(0, 20);
	window.draw(text);

	string status;
	if (getInvincibility())
		status = "Invincible";
	else
		status = "None";
	text.setString(status);
	text.setPosition(0, 40);
	window.draw(text);
}

void Player::setText(sf::Text& text_)
{
	text_.setFont(font);
	text_.setCharacterSize(24);
	text_.setFillColor(Color::Black);
	text_.setStyle(Text::Bold);
}

void Player::receiveMedal(int number)
{
	if (number > -1 && number < 8)
		allMedals[number]->setCollected(true);
}

void Player::receiveSkill()
{
	skills->setSkill();

	if (getObtainedSkill(CLIMB) && !sensors)
	{
		b2PolygonShape sensorSLeft, sensorSRight;

		sensorSLeft.SetAsBox(1.0f, 4.0f, b2Vec2(-8.0f, 0.0f), 0);
		sensorSRight.SetAsBox(1.0f, 4.0f, b2Vec2(8.0f, 0.0f), 0);

		b2FixtureDef sensorFDLeft, sensorFDRight;
		sensorFDLeft.shape = &sensorSLeft;
		sensorFDRight.shape = &sensorSRight;

		sensorFDLeft.isSensor = true;
		sensorFDRight.isSensor = true;

		getObject()->getBody()->CreateFixture(&sensorFDLeft);
		getObject()->getBody()->CreateFixture(&sensorFDRight);

		sensors = true;
	}
}

bool Player::getObtainedSkill(int skill)
{
	return skills->getSkill(skill);
}

void Player::upgrade(int stat)
{
	if (coins >= 2)
	{
		switch (stat)
		{
		case HP:
			setHP(getHP() + 10);
			curHp += 10;
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

Medal** Player::getActiveMedals()
{
	return activeMedals;
}

void Player::offMedal(int number)
{
	if (number > -1 && number < 2)
	{
		if (activeMedals[number]->getName() == "Boost HP")
		{
			setHP(getHP() - 50);
			if (getCurHP() > getHP())
				setCurHP(getHP());

			activeMedals[number]->setTriggered(false);
		}
		else if (activeMedals[number]->getName() == "Boost DMG")
		{
			setDMG(getDMG() - 50);
			activeMedals[number]->setTriggered(false);
		}
		activeMedals[number] = nullptr;
	}
}

void Player::onMedal(int number)
{
	for (int i = 0; i < 2; i++)
		if (activeMedals[i] && activeMedals[i]->getName() == allMedals[number]->getName())
			return;

	for (int i = 0; i < 2; i++)
		if (allMedals[number]->getCollected())
			if (!activeMedals[i] && number > -1 && number < 6)
			{
				activeMedals[i] = allMedals[number];
				break;
			}
}

void Player::checkCollision(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{
	vector<GameObject*>* gameObjects = Manager::getInstance()->getGame();

	Message m;
	for (b2ContactEdge* edge = getObject()->getBody()->GetContactList(); edge; edge = edge->next)
	{
		b2Contact* contact = edge->contact;

		for (auto x : *gameObjects)
		{
			if (contact->GetFixtureA() == x->getObject()->getBody()->GetFixtureList() || contact->GetFixtureB() == x->getObject()->getBody()->GetFixtureList())
				if (!contact->GetFixtureA()->IsSensor() && !contact->GetFixtureB()->IsSensor())
				{
					if (x->getDrawable()->getName() == "coin")
					{
						m.type = Erase;
						m.ctx.erase.objectToDelete = x;
						Manager::getInstance()->SendMessage(m);
						coins++;
						break;
					}
					else if (x->getDrawable()->getName() == "walking" || x->getDrawable()->getName() == "hiding")
					{
						if (time_span.count() > 3.0)
						{
							last_time = current_time;
							Message m;
							m.type = DealDmg;
							m.target = this;
							Entity* enemy = (Entity*)x;
							m.ctx.dealDmg.dmg = enemy->getDMG();
							Manager::getInstance()->SendMessage(m);
							break;
						}
					}
					else if (x->getDrawable()->getName() == "death")
					{
						last_time = current_time;
						Message m;
						m.type = DealDmg;
						m.target = this;
						m.ctx.dealDmg.dmg = this->getHP();
						Manager::getInstance()->SendMessage(m);
						break;
					}
					else if (x->getDrawable()->getName() == "skill")
					{
						m.type = Erase;
						m.ctx.erase.objectToDelete = x;
						Manager::getInstance()->SendMessage(m);
						receiveSkill();
						break;
					}
				}
		}
	}
}

int Player::getCurHP()
{
	return curHp;
}

void Player::setCurHP(int hp)
{
	curHp = hp;
}

int Player::getCoins()
{
	return coins;
}

void Player::setCoins(int c)
{
	coins = c;
}