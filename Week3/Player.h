#pragma once
#include "Character.h"

class Player : public Character
{
	Player(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	std::string ChooseAction() override;
};

