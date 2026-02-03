#pragma once
#include "Character.h"
#include <random>


class Enemy : public Character
{
public:
	Enemy(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	CharacterAction ChooseAction() override;
	void IncreaseDifficulty(int RoundNumber);

private:
	std::mt19937 Generator;
	std::uniform_int_distribution<int> Distribution;
};

