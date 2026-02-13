#pragma once
#include "Character.h"
#include <random>

enum class EnemyType : uint8_t
{
	SkeletonSpearman = 1,
	SkeletonWarrior,
	Viking,
	NormanWarrior
};

class Enemy : public Character
{
public:
	Enemy(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor);

	CharacterAction ChooseAction() override;
	void SetDefaultBaseValues();
	void IncreaseDifficultyTo(int RoundNumber);

private:
	std::mt19937 Generator;
	std::uniform_int_distribution<int> Distribution;
};

