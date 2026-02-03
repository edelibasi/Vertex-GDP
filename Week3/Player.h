#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	CharacterAction ChooseAction() override;
};

