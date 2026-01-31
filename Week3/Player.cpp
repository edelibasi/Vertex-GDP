#include "Player.h"


Player::Player(std::string Name, int Health, int Lives, int AttackPower, int Armor)
	: Character(Name, Health, Lives, AttackPower, Armor)
{
}

std::string Player::ChooseAction()
{
	// Implementation for player's action choice
}