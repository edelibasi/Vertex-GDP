#pragma once
#include <string>

enum class CharacterAction : uint8_t
{
	None, Attack, Parry, Defend, Rest
};

static const std::string GetActionName(CharacterAction Action);

class Character
{
public:
	virtual ~Character() = default;
	Character(std::string Name, int Health, int Stamina, int Lives, int AttackPower, int Armor);

	const std::string& GetName() const { return Name; }
	int GetHealth() const { return Health; }
	int GetLives() const { return Lives; }
	int GetAttackPower() const { return AttackPower; }
	int GetArmor() const { return Armor; }
	int GetStamina() const { return Stamina; }
	static int GetStaminaConsumption(CharacterAction Action);
	void SetBaseValues(int InHealth, int InStamina, int InLives, int InAttackPower, int InArmor);
	bool IsAlive() const { return Health > 0; }
	void UpdateHealth(int InHealth);
	void UpdateStamina(int InStamina);
	void UpdateLives(int InLives);
	void UpdateAttackPower(int InAttackPower);
	void UpdateArmor(int InArmor);

	virtual CharacterAction ChooseAction() = 0;

protected:
	std::string Name;
	int Health;
	int Stamina;
	int Lives;
	int AttackPower;
	int Armor;
};

