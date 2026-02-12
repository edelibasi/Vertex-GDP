#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor);

	CharacterAction ChooseAction() override;
	void SetDefaultBaseValues();
	void LevelUp(int RoundNumber);
};

