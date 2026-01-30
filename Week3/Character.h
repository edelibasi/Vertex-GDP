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
	Character(float Health, int Lives, float AttackPower);

	float GetHealth() const { return Health; }
	int GetLives() const { return Lives; }
	bool IsAlive() const;
	void UpdateHealth(float InHealth);
	void UpdateLives(int InLives);

	virtual std::string PerformAction(CharacterAction Action) = 0;

protected:
	float Health;
	int Lives;
	float AttackPower;
};

