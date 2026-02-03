#include "Character.h"
#include <iostream>

Character::Character(std::string Name, int Health, int Stamina, int Lives, int AttackPower, int Armor)
	: Name(Name), Health(Health), Stamina(Stamina), Lives(Lives), AttackPower(AttackPower), Armor(Armor)
{}

void Character::UpdateHealth(int InHealth)
{
	Health += InHealth;
	std::cout << Character::GetName() << "'s Current Health: " << Health << "\n" << std::endl;
}

void Character::UpdateStamina(int InStamina)
{
	Stamina += InStamina;
	if (Stamina > 100) { Stamina = 100; }
	std::cout << Character::GetName() << "'s Remaining Stamina: " << Stamina << "\n" << std::endl;
}

void Character::UpdateLives(int InLives)
{
	Lives += InLives;
	std::cout << Character::GetName() << "'s Remaining Lives: " << Lives << "\n" << std::endl;
}

void Character::UpdateAttackPower(int InAttackPower)
{
	AttackPower += InAttackPower;
	std::cout << Character::GetName() << "'s Attack Power: " << AttackPower << "\n" << std::endl;
}

void Character::UpdateArmor(int InArmor)
{
	AttackPower += InArmor;
	std::cout << Character::GetName() << "'s Armor: " << Armor << "\n" << std::endl;
}

int Character::GetStaminaConsumption(CharacterAction Action) const
{
	switch (Action) {
		case CharacterAction::Attack: return -10;
		case CharacterAction::Parry: return -20;
		case CharacterAction::Defend: return -5;
		case CharacterAction::Rest: return 20; // Resting restores stamina
		default: return 0;
	}
}

void Character::SetBaseValues(int InHealth, int InStamina, int InLives, int InAttackPower, int InArmor)
{
	Health = InHealth;
	Stamina = InStamina;
	Lives = InLives;
	AttackPower = InAttackPower;
	Armor = InArmor;
}
