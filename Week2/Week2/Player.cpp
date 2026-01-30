#include "Player.h"
#include <iostream>

Player::Player(float health, float stamina) :
	health(health),
	stamina(stamina)
{}

void Player::TakeDamage(float damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

void Player::PrintStatus() {
	std::cout << "Health: " << health << ", Stamina: " << stamina << std::endl;
}

void Player::Rest(float time) {
	stamina += time * 10; // Regain 10 stamina per unit time
	if (stamina > 100) {
		stamina = 100;
	}
}

void Player::Run(float time) {
	float staminaCost = time * 15; // Cost 15 stamina per unit time
	if (stamina >= staminaCost) {
		stamina -= staminaCost;
	} else {
		std::cout << "Not enough stamina to run for " << time << " units of time." << std::endl;
	}
}