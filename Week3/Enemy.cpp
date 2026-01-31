#include "Enemy.h"
#include <iostream>

Enemy::Enemy(std::string Name, int Health, int Lives, int AttackPower, int Armor) 
	: Character(Name, Health, Lives, AttackPower, Armor), Generator(std::random_device{}()), Distribution(0, 3)
{}

std::string Enemy::ChooseAction()
{
	switch (CharacterAction(Distribution(Generator)))
	{
	case Attack:
		AttackPower += 5.0f;
		std::cout << Name << " increases its Attack Power to " << AttackPower << "!" << std::endl;
		break;

	case Parry:
		break;

	case Defend:
		break;

	case Heal:
		break;

	default:
		throw std::runtime_error("Invalid action chosen by Enemy.");
		break;
	}
}

void Enemy::IncreaseStrength(int RoundNumber)
{
	switch (RoundNumber)
	{
	case 1:
		return;

	case 2:
		Health += RoundNumber;
		std::cout << Name << " increases its Attack Power to " << AttackPower << "!" << std::endl;
		break;
	case 3:
		AttackPower += RoundNumber;
		Health += RoundNumber;
		std::cout << Name << " increases its Attack Power to " << AttackPower << "!" << std::endl;
		break;
	case 4:
		AttackPower += RoundNumber;
		Health += RoundNumber;
		std::cout << Name << " increases its Attack Power to " << AttackPower << "!" << std::endl;
		break;
	case 5:
		AttackPower += RoundNumber;
		Health += RoundNumber;
		Armor += RoundNumber / 2;
		std::cout << Name << " increases its Attack Power to " << AttackPower << "!" << std::endl;
		break;

	default:
		break;
	}
	
}
