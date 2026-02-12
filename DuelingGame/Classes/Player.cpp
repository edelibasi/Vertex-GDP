#include "Player.h"
#include <raylib.h>

Player::Player(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor)
	: Character(Name, Health, Stamina, Lives, AttackPower, Armor)
{}

CharacterAction Player::ChooseAction()
{
	CharacterAction Action = CharacterAction::None;

	if (IsKeyPressed(KEY_ONE))        Action = CharacterAction::Attack;
	else if (IsKeyPressed(KEY_TWO))   Action = CharacterAction::Parry;
	else if (IsKeyPressed(KEY_THREE)) Action = CharacterAction::Defend;
	else if (IsKeyPressed(KEY_FOUR))  Action = CharacterAction::Rest;

	return Action;
}

void Player::SetDefaultBaseValues()
{
	SetBaseValues(100, 100, GetLives(), 20, 10);
}

void Player::LevelUp(int RoundNumber)
{
	UpdateHealth(RoundNumber * 10);
	UpdateAttackPower(RoundNumber * 10);
	UpdateArmor((RoundNumber * 10) / 2);
}
