#pragma once
#include "Character.h"
#include <random>


class Enemy : public Character
{
public:
	Enemy(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor);

	CharacterAction ChooseAction() override;
	void IncreaseDifficultyTo(int RoundNumber);

private:
	std::mt19937 Generator;
	std::uniform_int_distribution<int> Distribution;
};

