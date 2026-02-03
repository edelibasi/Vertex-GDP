#pragma once
#include <string>

enum CharacterAction : int
{
	Attack = 1, Parry, Defend
};

class Character
{
public:
	Character(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	std::string GetName() const { return Name; }
	int GetHealth() const { return Health; }
	int GetLives() const { return Lives; }
	bool IsAlive() const { return Health > 0; }
	void UpdateHealth(int InHealth);
	void UpdateLives(int InLives);


	virtual CharacterAction ChooseAction() = 0;

protected:
	std::string Name;
	int Health;
	int Lives;
	int AttackPower;
	int Armor;
};

