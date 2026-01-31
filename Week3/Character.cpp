#include "Character.h"
#include <iostream>

Character::Character(std::string Name, int Health, int Lives, int AttackPower, int Armor)
	: Name(Name), Health(Health), Lives(Lives), AttackPower(AttackPower), Armor(Armor)
{}

bool Character::IsAlive() const
{
	return Health > 0;
}

void Character::UpdateHealth(int InHealth)
{
	Health += InHealth;
	std::cout << "Current Health: " << Health << std::endl;
}

void Character::UpdateLives(int InLives)
{
	Lives += InLives;
	std::cout << "Remaining Lives: " << Lives << std::endl;
}
