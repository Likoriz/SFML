#include "Entity.h"

Entity::Entity(std::string name)
{
}

bool Entity::checkRadius()
{
	return false;
}

void Entity::setHP(int hp_)
{
	hp = hp_;
}

void Entity::setDMG(int dmg)
{
	damage = dmg;
}

void Entity::setDEF(int def)
{
	defense = def;
}

void Entity::setRadius(int rad)
{
	radius = rad;
}

int Entity::getHP()
{
	return hp;
}

int Entity::getDMG()
{
	return damage;
}

int Entity::getDEF()
{
	return defense;
}

int Entity::getRadius()
{
	return radius;
}