#include "Enemy.h"
#include <iostream>

Enemy::Enemy(std::string Name, int Health, int Stamina, int Lives, int AttackPower, int Armor) 
	: Character(Name, Health, Stamina, Lives, AttackPower, Armor), Generator(std::random_device{}()), Distribution(1, 4)
{}

CharacterAction Enemy::ChooseAction()
{
	CharacterAction Action = CharacterAction(Distribution(Generator));
	UpdateStamina(GetStaminaConsumption(Action));
	return Action;
}

void Enemy::IncreaseDifficultyTo(int RoundNumber)
{
	switch (RoundNumber)
	{
	case 1:
		return;

	case 2:
		Name = "Goblin Warrior";
		UpdateHealth(RoundNumber * 10);
		
		break;
	case 3:
		Name = "Gladiator";
		UpdateHealth(RoundNumber * 10);
		UpdateAttackPower(RoundNumber * 10);
		
		break;
	case 4:
		Name = "Berserker";
		UpdateHealth(RoundNumber * 10);
		UpdateAttackPower(RoundNumber * 10);
		
		break;
	case 5:
		Name = "Knight Champion";
		UpdateHealth(RoundNumber * 10);
		UpdateAttackPower(RoundNumber * 10);
		UpdateArmor((RoundNumber * 10) / 2);
		break;

	default:
		break;
	}
	
}
