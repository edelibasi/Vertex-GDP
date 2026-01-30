#pragma once

class Player {

public:
	Player(float health, float stamina);
	void TakeDamage(float damage);
	void PrintStatus();
	void Rest(float time);
	void Run(float time);

private:
	float health;
	float stamina;
};

