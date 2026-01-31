#pragma once
#include "Character.h"
#include <random>


class Enemy : public Character
{
public:
	Enemy(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	std::string ChooseAction() override;
	void IncreaseStrength(int RoundNumber);

private:
	std::mt19937 Generator;
	std::uniform_int_distribution<int> Distribution;
};

