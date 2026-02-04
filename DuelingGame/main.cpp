#include <iostream>
#include "Player.h"
#include "Enemy.h"

int main()
{
	Player MainPlayer("Hero", 100, 100, 3, 20, 10);
	Enemy MainEnemy("Goblin", 80, 100, 1, 15, 0);

	std::cout << "Battle: " << MainPlayer.GetName() << " vs " << MainEnemy.GetName() << std::endl;
	int RoundNumber = 1;

	while (MainPlayer.IsAlive())
	{
		CharacterAction PlayerAction = MainPlayer.ChooseAction();
		CharacterAction EnemyAction = MainEnemy.ChooseAction();

		// Here you would implement the logic to resolve the actions chosen by the player and enemy
		if (MainPlayer.GetStamina() < -MainPlayer.GetStaminaConsumption(PlayerAction))
		{
			std::cout << MainPlayer.GetName() << " is too exhausted to perform the action and must rest!\n" << std::endl;
			MainPlayer.UpdateStamina(MainPlayer.GetStaminaConsumption(CharacterAction::Rest));
			PlayerAction = CharacterAction::Rest;
		}

		if (MainEnemy.GetStamina() < -MainEnemy.GetStaminaConsumption(PlayerAction))
		{
			std::cout << MainEnemy.GetName() << " is too exhausted to perform the action and must rest!\n" << std::endl;
			MainEnemy.UpdateStamina(MainEnemy.GetStaminaConsumption(CharacterAction::Rest));
			EnemyAction = CharacterAction::Rest;
		}

		if (PlayerAction == CharacterAction::Attack && EnemyAction == CharacterAction::Attack)
		{
			std::cout << "\n" <<MainPlayer.GetName() << " and " << MainEnemy.GetName() << " both attack!\n" << std::endl;
			std::cout << "It's a clash! The weapons ring as they hit each other!\n" << std::endl;
		}
		else if (PlayerAction == CharacterAction::Attack && EnemyAction == CharacterAction::Parry) {
			std::cout << MainEnemy.GetName() << " parries the attack!\n" << std::endl;
			MainPlayer.UpdateHealth(-(MainEnemy.GetAttackPower() - MainPlayer.GetArmor()));
		}
		else if (PlayerAction == CharacterAction::Attack && EnemyAction == CharacterAction::Defend) {
			std::cout << MainEnemy.GetName() << " defends against the attack!\n" << std::endl;
			std::cout << "The attack is less successful!\n" << std::endl;
			MainEnemy.UpdateHealth(-((MainPlayer.GetAttackPower() - MainEnemy.GetArmor()) / 2));
		}
		else if (PlayerAction == CharacterAction::Attack && EnemyAction == CharacterAction::Rest) {
			std::cout << MainEnemy.GetName() << " caught resting while "<< MainPlayer.GetName() << " unleashes an attack!\n" << std::endl;
			MainEnemy.UpdateHealth(-(MainPlayer.GetAttackPower() - MainEnemy.GetArmor()));
		}
		else if (PlayerAction == CharacterAction::Defend && EnemyAction == CharacterAction::Attack) {
			std::cout << MainPlayer.GetName() << " defends against the attack!\n" << std::endl;
			std::cout << "The attack is less successful!\n" << std::endl;
			MainPlayer.UpdateHealth(-((MainEnemy.GetAttackPower() - MainPlayer.GetArmor()) / 2));
		}
		else if (PlayerAction == CharacterAction::Parry && EnemyAction == CharacterAction::Attack) {
			std::cout << MainPlayer.GetName() << " parries the attack!\n" << std::endl;
			MainEnemy.UpdateHealth(-(MainPlayer.GetAttackPower() - MainEnemy.GetArmor()));
		}
		else if (PlayerAction == CharacterAction::Rest && EnemyAction == CharacterAction::Attack) {
			std::cout << MainPlayer.GetName() << " caught resting while " << MainEnemy.GetName() << " unleashes an attack!\n" << std::endl;
			MainPlayer.UpdateHealth(-(MainEnemy.GetAttackPower() - MainPlayer.GetArmor()));
		}
		else {
			std::cout << MainPlayer.GetName() << " decided to " << GetActionName(PlayerAction) << "\n" << std::endl;
			std::cout << MainEnemy.GetName() << " decided to " << GetActionName(EnemyAction) << "\n" << std::endl;
		}

		if (!MainEnemy.IsAlive())
		{
			std::cout << MainEnemy.GetName() << " has been defeated!" << std::endl;
			std::cout << MainPlayer.GetName() << " wins the battle!\n" << std::endl;
			RoundNumber++;

			if (RoundNumber > 5)
			{
				std::cout << "Congratulations! You have defeated all enemies!" << std::endl;
				break;
			}

			MainPlayer.SetBaseValues(100, 100, 3, 20, 10);
			MainEnemy.SetBaseValues(80, 100, 1, 15, 0);
			
			MainPlayer.LevelUp(RoundNumber);
			std::cout << "A new stronger enemy appears!" << std::endl;
			MainEnemy.IncreaseDifficultyTo(RoundNumber);
			

		}
		else if (!MainPlayer.IsAlive()) {
			std::cout << MainPlayer.GetName() << " has lost a life!" << std::endl;

			if (MainPlayer.GetLives() > 1)
			{
				MainPlayer.UpdateLives(-1);
				MainPlayer.SetBaseValues(100, 100, MainPlayer.GetLives(), 20, 10);
				std::cout << MainPlayer.GetName() << " respawns to continue the battle!" << std::endl;
			}
			else {
				std::cout << MainPlayer.GetName() << " has no lives left!" << std::endl;
				std::cout << MainEnemy.GetName() << " is the ultimate victor!" << std::endl;
				break;
			}
			std::cout << MainEnemy.GetName() << " wins the battle!" << std::endl;
			break;
		}
	}

	return 0;
}