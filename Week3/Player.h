#pragma once
#include "Character.h"

class Player : public Character
{
	Player(float Health, int Lives, float AttackPower)
		: Character(Health, Lives, AttackPower)
	{}

};

