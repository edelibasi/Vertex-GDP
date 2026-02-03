#include "Player.h"
#include <iostream>

Player::Player(std::string Name, int Health, int Lives, int AttackPower, int Armor)
	: Character(Name, Health, Lives, AttackPower, Armor)
{
}

CharacterAction Player::ChooseAction()
{
	int Input = -1;
	while (true)
	{
		std::cout << "Choose your action:\n1. Attack\n2. Parry\n3. Defend\n\n";
		std::cin >> Input;

		if (std::cin.fail())
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
		} else {
			return CharacterAction(Input);
			break;
		}
	}
}