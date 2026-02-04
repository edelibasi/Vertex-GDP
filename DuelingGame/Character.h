#pragma once
#include <string>

enum class CharacterAction : int
{
	Attack = 1, Parry, Defend, Rest
};

static const std::string GetActionName(CharacterAction Action)
{
	switch (Action) {
		case CharacterAction::Attack: return "Attack";
		case CharacterAction::Parry: return "Parry";
		case CharacterAction::Defend: return "Defend";
		case CharacterAction::Rest: return "Rest";
		default: return "Unknown Action";
	}
}

class Character
{
public:
	Character(const std::string& Name, int Health, int Stamina, int Lives, int AttackPower, int Armor);

	const std::string& GetName() const { return Name; }
	int GetHealth() const { return Health; }
	int GetLives() const { return Lives; }
	int GetAttackPower() const { return AttackPower; }
	int GetArmor() const { return Armor; }
	int GetStamina() const { return Stamina; }
	int GetStaminaConsumption(CharacterAction Action) const;
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

