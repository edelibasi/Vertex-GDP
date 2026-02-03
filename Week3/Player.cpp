#include "Player.h"
#include <iostream>

Player::Player(std::string Name, int Health, int Stamina, int Lives, int AttackPower, int Armor)
	: Character(Name, Health, Stamina, Lives, AttackPower, Armor)
{
}

CharacterAction Player::ChooseAction()
{
	int Input = -1;
	while (true)
	{
		std::cout << "\nChoose your action:\n1. Attack\n2. Parry\n3. Defend\n4. Rest\n\n";
		std::cin >> Input;

		if (std::cin.fail())
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
		} else {
			UpdateStamina(GetStaminaConsumption(CharacterAction(Input)));
			return CharacterAction(Input);
			break;
		}
	}
}

void Player::LevelUp(int RoundNumber)
{
	std::cout << Name << " has leveled up! Attack Power and Armor increased.\n" << std::endl;
	UpdateHealth(RoundNumber * 10);
	UpdateAttackPower(RoundNumber * 10);
	UpdateArmor((RoundNumber * 10) / 2);
}