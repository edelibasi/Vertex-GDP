#include "Player.h"
#include "Logger.h"
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

	if (Action != CharacterAction::None)
		UpdateStamina(GetStaminaConsumption(Action));

	return Action;
}

void Player::LevelUp(int RoundNumber)
{
	Logger::LogMessage(LogLevel::INFO, Name + " has leveled up! Attack Power and Armor increased.");
	UpdateHealth(RoundNumber * 10);
	UpdateAttackPower(RoundNumber * 10);
	UpdateArmor((RoundNumber * 10) / 2);
}