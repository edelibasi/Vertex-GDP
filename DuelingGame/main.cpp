#include "Enemy.h"
#include "Player.h"
#include "UILayout+Constants.h"
#include "raylib.h"
#include <string>
#include <map>
#include <functional>
#include "GameMessage.h"
#include "ImageStore.h"

enum class GameState: uint8_t
{
	Battle,
	EnemyDefeated,
	PlayerDefeated,
	GameWon,
	GameOver
};

struct CombatOutcome {
	GameMessage Message;
	std::function<void(Player&, Enemy&)> ResolveEffects;
};

static void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy, GameMessage& Message, CharacterAction& OutPlayerAction, CharacterAction& OutEnemyAction);
static void RenderGameState(const Player& MainPlayer, const Enemy& MainEnemy, int RoundNumber, const GameMessage& Message, CharacterAction PlayerAction, CharacterAction EnemyAction);
static void ResetRound(Player& MainPlayer, Enemy& MainEnemy, int RoundNumber);

int main()
{
	InitWindow(UILayout_Constants::SCREEN_WIDTH, UILayout_Constants::SCREEN_HEIGHT, "Dueling Game");
	SetTargetFPS(GameConstants::TARGET_FPS);

	Player MainPlayer("Hero", 100, 100, 3, 20, 10);
	Enemy MainEnemy("Goblin", 80, 100, 1, 15, 0);
	int RoundNumber = 1;
	GameState CurrentState = GameState::Battle;
	GameMessage CurrentMessage = GameMessage();
	CharacterAction LastPlayerAction = CharacterAction::None;
	CharacterAction LastEnemyAction = CharacterAction::None;
	Texture2D background = LoadTexture(ImageStore::Background.c_str());

	while (!WindowShouldClose())
	{
		// Update game state
		if (CurrentState == GameState::Battle)
		{
			ProcessOutcome(MainPlayer, MainEnemy, CurrentMessage, LastPlayerAction, LastEnemyAction);

			if (!MainEnemy.IsAlive())
			{
				CurrentState = GameState::EnemyDefeated;
				CurrentMessage = GameMessage(
					MainEnemy.GetName() + " has been defeated by " + MainPlayer.GetName() + "!"
				);
			}
			else if (!MainPlayer.IsAlive())
			{
				CurrentState = GameState::PlayerDefeated;
			}
		}
		else if (CurrentState == GameState::EnemyDefeated)
		{
			if (!CurrentMessage.IsActive())
			{
				RoundNumber++;
				if (RoundNumber > GameConstants::MAX_ROUNDS)
				{
					CurrentState = GameState::GameWon;
					CurrentMessage = GameMessage(
						MainPlayer.GetName() + " has emerged victorious",
						"after defeating all enemies!"
					);
				}
				else
				{
					ResetRound(MainPlayer, MainEnemy, RoundNumber);
					CurrentState = GameState::Battle;
				}
			}
		}
		else if (CurrentState == GameState::PlayerDefeated)
		{
			if (MainPlayer.GetLives() > 1)
			{
				MainPlayer.UpdateLives(-1);
				MainPlayer.SetDefaultBaseValues();
				CurrentMessage = GameMessage(
					MainPlayer.GetName() + " has lost a life!",
					MainPlayer.GetName() + " respawns to continue the battle!"
				);
				CurrentState = GameState::Battle;
			}
			else
			{
				CurrentState = GameState::GameOver;
				CurrentMessage = GameMessage(
					MainPlayer.GetName() + " has no lives left!",
					MainEnemy.GetName() + " is the ultimate victor!"
				);
			}
		}

		CurrentMessage.Update();

		// Render
		BeginDrawing();
		ClearBackground(GameColors::BACKGROUND);
		DrawTexture(background, 0, 0, WHITE);
		
		RenderGameState(MainPlayer, MainEnemy, RoundNumber, CurrentMessage, LastPlayerAction, LastEnemyAction);
		if (CurrentState == GameState::Battle)
		{
			DrawText(
				"1.Attack  2.Parry  3.Defend  4.Rest",
				UILayout_Constants::TEXT_X,
				UILayout_Constants::ROUND_Y + 30,
				UILayout_Constants::TEXT_SIZE, GameColors::SUCCESS
				);
		}
		EndDrawing();

		// Exit conditions
		if ((CurrentState == GameState::GameWon || CurrentState == GameState::GameOver) && !CurrentMessage.IsActive())
		{
			break;
		}
	}

	UnloadTexture(background);
	CloseWindow();
	return 0;
}

void ProcessOutcome(
	Player& MainPlayer,
	Enemy& MainEnemy,
	GameMessage& Message,
	CharacterAction& OutPlayerAction,
	CharacterAction& OutEnemyAction)
{
	CharacterAction PlayerAction = MainPlayer.ChooseAction();
	if (PlayerAction == CharacterAction::None) return;
	CharacterAction EnemyAction = MainEnemy.ChooseAction();
	
	OutPlayerAction = PlayerAction;
	OutEnemyAction = EnemyAction;

	// Check stamina before performing actions
	if (MainPlayer.GetStamina() < -Player::GetStaminaConsumption(PlayerAction))
	{
		Message = GameMessage(MainPlayer.GetName() + " is too exhausted and must rest!");
		MainPlayer.UpdateStamina(Player::GetStaminaConsumption(CharacterAction::Rest));
		OutPlayerAction = CharacterAction::Rest;
		return;
	}

	if (MainEnemy.GetStamina() < -Enemy::GetStaminaConsumption(EnemyAction))
	{
		Message = GameMessage(MainEnemy.GetName() + " is too exhausted and must rest!");
		MainEnemy.UpdateStamina(Enemy::GetStaminaConsumption(CharacterAction::Rest));
		OutEnemyAction = CharacterAction::Rest;
		return;
	}
	
	using ActionPair = std::pair<CharacterAction, CharacterAction>;
	std::map<ActionPair, CombatOutcome> OutcomeMap = 
	{
		{{CharacterAction::Attack, CharacterAction::Attack},
		{GameMessage("Clash!", "Both warriors exchange blows!"),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Attack, CharacterAction::Parry},
		{GameMessage(MainEnemy.GetName() + " parries the attack!", "", "", GameMessage::Type::Error),
		[](Player& Player, const Enemy& Enemy) { Player.UpdateHealth(-(Player.GetAttackPower() - Enemy.GetArmor())); }}},

		{{CharacterAction::Attack, CharacterAction::Defend},
		{GameMessage(MainEnemy.GetName() + " blocks the attack!", "Reduced damage!", "", GameMessage::Type::Warning),
		[](const Player& Player, Enemy& Enemy) { Enemy.UpdateHealth(-((Player.GetAttackPower() - Enemy.GetArmor()) / 2)); }}},

		{{CharacterAction::Attack, CharacterAction::Rest},
		{GameMessage(MainEnemy.GetName() + " is caught off guard!", "Direct hit!", "", GameMessage::Type::Success),
		[](const Player& Player, Enemy& Enemy) { Enemy.UpdateHealth(-(Player.GetAttackPower() - Enemy.GetArmor())); }}},

		{{CharacterAction::Parry, CharacterAction::Attack},
		{GameMessage(MainPlayer.GetName() + " parries!", "", "", GameMessage::Type::Success),
		[](const Player& Player, Enemy& Enemy) { Enemy.UpdateHealth(-(Enemy.GetAttackPower() - Player.GetArmor())); }}},

		{{CharacterAction::Parry, CharacterAction::Parry},
		{GameMessage("Deadlock!", "Neither lands a blow."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Parry, CharacterAction::Defend},
		{GameMessage("Tense standoff.", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Parry, CharacterAction::Rest},
		{GameMessage(MainEnemy.GetName() + " gathers strength while " + MainPlayer.GetName() + " tries to thwart an attack!", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Defend, CharacterAction::Attack},
		{GameMessage(MainPlayer.GetName() + " braces for impact!", "Reduced damage!", "", GameMessage::Type::Warning),
		[](Player& Player, const Enemy& Enemy) { Player.UpdateHealth(-((Enemy.GetAttackPower() - Player.GetArmor()) / 2)); }}},

		{{CharacterAction::Defend, CharacterAction::Parry},
		{GameMessage("Mutual defense.", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Defend, CharacterAction::Defend},
		{GameMessage("Both prepare defenses.", "A stalemate ensues."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Defend, CharacterAction::Rest},
		{GameMessage(MainPlayer.GetName() + " prepares to defend while " + MainEnemy.GetName() + " is resting!", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Rest, CharacterAction::Attack},
		{GameMessage(MainPlayer.GetName() + " is caught resting!", "Direct hit!", "", GameMessage::Type::Error),
		[](Player& Player, const Enemy& Enemy) { Player.UpdateHealth(-(Enemy.GetAttackPower() - Player.GetArmor())); }}},

		{{CharacterAction::Rest, CharacterAction::Parry},
		{GameMessage(MainPlayer.GetName() + " gathers strength while " + MainEnemy.GetName() + " tries to thwart an attack!", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Rest, CharacterAction::Defend},
		{GameMessage(MainPlayer.GetName() + " gathers strength while " + MainEnemy.GetName() + " prepares to defend!", "Nothing happens."),
		[](Player& Player, Enemy& Enemy) {}}},

		{{CharacterAction::Rest, CharacterAction::Rest},
		{GameMessage("Both warriors rest!", "Respite in battle."),
		[](Player& Player, Enemy& Enemy) {}}}
	};

	CombatOutcome Outcome = OutcomeMap[{ OutPlayerAction, OutEnemyAction }];
	Message = Outcome.Message;
	Outcome.ResolveEffects(MainPlayer, MainEnemy);
}

void RenderGameState(
	const Player& MainPlayer,
	const Enemy& MainEnemy,
	int RoundNumber,
	const GameMessage& Message,
	CharacterAction PlayerAction,
	CharacterAction EnemyAction
	)
{
	// Title & Round Info
	DrawText(
		("Battle: " + MainPlayer.GetName() + " vs " + MainEnemy.GetName()).c_str(),
		UILayout_Constants::TEXT_X, 
		UILayout_Constants::TITLE_Y,
		UILayout_Constants::TEXT_SIZE,
		GameColors::TEXT
		);
	DrawText(
		("Round: " + std::to_string(RoundNumber)).c_str(),
		UILayout_Constants::TEXT_X,
		UILayout_Constants::ROUND_Y,
		UILayout_Constants::TEXT_SIZE,
		GameColors::TEXT
		);
	
	// Messages
	if (Message.IsActive())
	{
		if (!Message.Line1.empty())
			DrawText(
				Message.Line1.c_str(),
				UILayout_Constants::TEXT_X_CENTER,
				UILayout_Constants::MESSAGE_LINE1_Y,
				UILayout_Constants::TEXT_SIZE,
				Message.GetColor()
				);
		if (!Message.Line2.empty())
			DrawText(
				Message.Line2.c_str(),
				UILayout_Constants::TEXT_X_CENTER,
				UILayout_Constants::MESSAGE_LINE2_Y,
				UILayout_Constants::TEXT_SIZE,
				Message.GetColor()
				);
		if (!Message.Line3.empty())
			DrawText(
				Message.Line3.c_str(),
				UILayout_Constants::TEXT_X_CENTER,
				UILayout_Constants::MESSAGE_LINE3_Y,
				UILayout_Constants::TEXT_SIZE,
				Message.GetColor()
				);
	}
}

void ResetRound(Player& MainPlayer, Enemy& MainEnemy, int RoundNumber)
{
	MainPlayer.SetDefaultBaseValues();
	MainEnemy.SetDefaultBaseValues();
	MainPlayer.LevelUp(RoundNumber);
	MainEnemy.IncreaseDifficultyTo(RoundNumber);
}