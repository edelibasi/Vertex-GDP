#include <iostream>
#include "Player.h"
#include "Enemy.h"

int main()
{
	Player MainPlayer("Hero", 100, 3, 20, 10);
	Enemy MainEnemy("Goblin", 80, 2, 15, 0);

	std::cout << MainPlayer.GetName() << " vs " << MainEnemy.GetName() << std::endl;

	while (MainPlayer.IsAlive())
	{
		CharacterAction PlayerAction = MainPlayer.ChooseAction();
		CharacterAction EnemyAction = MainEnemy.ChooseAction();

		// Here you would implement the logic to resolve the actions chosen by the player and enemy
		if (PlayerAction == Attack && EnemyAction == Attack)
		{
			std::cout << MainPlayer.GetName() << " and " << MainEnemy.GetName() << " both attack!" << std::endl;
			// Implement attack resolution logic here
		}
		else if (PlayerAction == Attack && EnemyAction == Parry) {
			std::cout << MainEnemy.GetName() << " parries the attack!" << std::endl;
			// Implement parry logic here
		}
		else if (PlayerAction == Attack && EnemyAction == Defend) {
			std::cout << MainEnemy.GetName() << " defends against the attack!" << std::endl;
			// Implement defend logic here
		}
		else if (PlayerAction == Defend && EnemyAction == Attack) {
			std::cout << MainPlayer.GetName() << " defends against the attack!" << std::endl;
			// Implement defend logic here
		}
		else if (PlayerAction == Parry && EnemyAction == Attack) {
			std::cout << MainPlayer.GetName() << " parries the attack!" << std::endl;
			// Implement parry logic here
		}

		if (!MainEnemy.IsAlive())
		{
			std::cout << MainEnemy.GetName() << " has been defeated!" << std::endl;
			std::cout << MainPlayer.GetName() << " wins the battle!" << std::endl;
			break;
		}
	}

	return 0;
}