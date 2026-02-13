#include "Enemy.h"

Enemy::Enemy(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor) 
	: Character(Name, Health, Stamina, Lives, AttackPower, Armor), Generator(std::random_device{}()), Distribution(1, 4)
{}

CharacterAction Enemy::ChooseAction()
{
	CharacterAction Action = CharacterAction(Distribution(Generator));
	return Action;
}

void Enemy::SetDefaultBaseValues()
{
	SetBaseValues(80, 100, 1, 15, 0);
}

void Enemy::IncreaseDifficultyTo(int RoundNumber)
{
	switch (RoundNumber)
	{
	case 1:
		return;

	case 2:
		Name = "Skeleton Warrior";
		UpdateHealth(RoundNumber * 10);
		
		break;
	case 3:
		Name = "Viking";
		UpdateHealth(RoundNumber * 10);
		UpdateAttackPower(RoundNumber * 10);
		
		break;
	case 4:
		Name = "Norman Warrior";
		UpdateHealth(RoundNumber * 10);
		UpdateAttackPower(RoundNumber * 10);
		
		break;
	default:
		break;
	}
	
}
