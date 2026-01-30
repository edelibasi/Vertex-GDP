#include "Character.h"
#include <iostream>

Character::Character(float Health, int Lives, float AttackPower)
	: Health(Health), Lives(Lives), AttackPower(AttackPower)
{}

bool Character::IsAlive() const
{
	return Health > 0.0f;
}

void Character::UpdateHealth(float InHealth)
{
	Health += InHealth;
	std::cout << "Current Health: " << Health << std::endl;
}

void Character::UpdateLives(int InLives)
{
	Lives += InLives;
	std::cout << "Remaining Lives: " << Lives << std::endl;
}
