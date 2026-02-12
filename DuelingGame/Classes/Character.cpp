#include "Character.h"
#include <algorithm>

Character::Character(std::string Name, int Health, int Stamina, int Lives, int AttackPower, int Armor)
	: Name(std::move(Name)), Health(Health), Stamina(Stamina), Lives(Lives), AttackPower(AttackPower), Armor(Armor)
{}

int Character::GetStaminaConsumption(CharacterAction Action)
{
	switch (Action)
	{
	case CharacterAction::None: return 0;
	case CharacterAction::Attack: return -10;
	case CharacterAction::Parry: return -20;
	case CharacterAction::Defend: return -5;
	case CharacterAction::Rest: return 20; // Resting restores stamina
	}
	return 0;
}

void Character::SetBaseValues(int InHealth, int InStamina, int InLives, int InAttackPower, int InArmor)
{
	Health = InHealth;
	Stamina = InStamina;
	Lives = InLives;
	AttackPower = InAttackPower;
	Armor = InArmor;
}

void Character::UpdateHealth(int InHealth)
{
	Health += InHealth;
	Health = std::max(Health, 0);
}

void Character::UpdateStamina(int InStamina)
{
	Stamina += InStamina;
	Stamina = std::min(Stamina, 100);
}

void Character::UpdateLives(int InLives)
{
	Lives += InLives;
	Lives = std::max(Lives, 0);
}

void Character::UpdateAttackPower(int InAttackPower)
{
	AttackPower += InAttackPower;
}

void Character::UpdateArmor(int InArmor)
{
	Armor += InArmor;
}
