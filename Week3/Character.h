#pragma once
#include <string>

enum CharacterAction : int
{
	Attack,
	Parry,
	Defend,
	Heal
};

class Character
{
public:
	Character(std::string Name, int Health, int Lives, int AttackPower, int Armor);

	int GetHealth() const { return Health; }
	int GetLives() const { return Lives; }
	bool IsAlive() const;
	void UpdateHealth(int InHealth);
	void UpdateLives(int InLives);

	virtual std::string ChooseAction() = 0;

protected:
	std::string Name;
	int Health;
	int Lives;
	int AttackPower;
	int Armor;
};

