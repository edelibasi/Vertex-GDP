#include "Enemy.h"
#include "Player.h"
#include "UILayout+Constants.h"
#include "raylib.h"
#include <string>
#include <map>
#include <functional>
#include <ostream>
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

enum class CombatOutcomeType : uint8_t
{
	Clash,
	ParriedByEnemy,
	BlockedByEnemy,
	HitEnemy,
	ParriedByPlayer,
	Deadlock,
	StandoffParryDefend,
	ParryRest,
	BlockedByPlayer,
	DefendParry,
	BothDefend,
	DefendRest,
	HitPlayer,
	RestParry,
	RestDefend,
	BothRest
};

struct CombatOutcome {
	GameMessage Message;
	std::function<void(Player&, Enemy&)> ResolveEffects;
};

float TIME_SINCE_LAST_INPUT = 0.0f;
float InputCooldown = 3.5f;

static void ProcessCharacterActions(Player& MainPlayer, Enemy& MainEnemy, GameMessage& Message);
static CombatOutcome BuildOutcome(CombatOutcomeType Type, const Player& MainPlayer, const Enemy& MainEnemy);
static void RenderGameState(const Player& MainPlayer, const Enemy& MainEnemy, int RoundNumber, const GameMessage& Message);
static void ResetRound(Player& MainPlayer, Enemy& MainEnemy, int RoundNumber);

using ActionPair = std::pair<CharacterAction, CharacterAction>;
static const std::map<ActionPair, CombatOutcomeType> OutcomeTypeMap =
{
	{{CharacterAction::Attack, CharacterAction::Attack},  CombatOutcomeType::Clash},
	{{CharacterAction::Attack, CharacterAction::Parry},   CombatOutcomeType::ParriedByEnemy},
	{{CharacterAction::Attack, CharacterAction::Defend},  CombatOutcomeType::BlockedByEnemy},
	{{CharacterAction::Attack, CharacterAction::Rest},    CombatOutcomeType::HitEnemy},
	{{CharacterAction::Parry,  CharacterAction::Attack},  CombatOutcomeType::ParriedByPlayer},
	{{CharacterAction::Parry,  CharacterAction::Parry},   CombatOutcomeType::Deadlock},
	{{CharacterAction::Parry,  CharacterAction::Defend},  CombatOutcomeType::StandoffParryDefend},
	{{CharacterAction::Parry,  CharacterAction::Rest},    CombatOutcomeType::ParryRest},
	{{CharacterAction::Defend, CharacterAction::Attack},  CombatOutcomeType::BlockedByPlayer},
	{{CharacterAction::Defend, CharacterAction::Parry},   CombatOutcomeType::DefendParry},
	{{CharacterAction::Defend, CharacterAction::Defend},  CombatOutcomeType::BothDefend},
	{{CharacterAction::Defend, CharacterAction::Rest},    CombatOutcomeType::DefendRest},
	{{CharacterAction::Rest,   CharacterAction::Attack},  CombatOutcomeType::HitPlayer},
	{{CharacterAction::Rest,   CharacterAction::Parry},   CombatOutcomeType::RestParry},
	{{CharacterAction::Rest,   CharacterAction::Defend},  CombatOutcomeType::RestDefend},
	{{CharacterAction::Rest,   CharacterAction::Rest},    CombatOutcomeType::BothRest}
};

int main()
{
	InitWindow(UILayout_Constants::SCREEN_WIDTH, UILayout_Constants::SCREEN_HEIGHT, "Dueling Game");
	SetTargetFPS(GameConstants::TARGET_FPS);

	Player MainPlayer("Hero", 100, 100, 3, 20, 10);
	Enemy MainEnemy("Skeleton Spearman", 80, 100, 1, 15, 0);
	int RoundNumber = 1;
	GameState CurrentState = GameState::Battle;
	GameMessage CurrentMessage = GameMessage();
	CharacterAction LastPlayerAction = CharacterAction::None;
	CharacterAction LastEnemyAction = CharacterAction::None;
	Texture2D background = LoadTexture(ImageStore::Background.c_str());
	
	if (background.id == 0)
		TraceLog(LOG_WARNING, "Failed to load background texture: %s", ImageStore::Background.c_str());

	while (!WindowShouldClose())
	{
		TIME_SINCE_LAST_INPUT += GetFrameTime();
		// Update game state
		switch (CurrentState)
		{
		case GameState::Battle:
			ProcessCharacterActions(MainPlayer, MainEnemy, CurrentMessage);

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
			break;

		case GameState::EnemyDefeated:
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
			break;

		case GameState::PlayerDefeated:
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
			break;

		case GameState::GameWon:
		case GameState::GameOver:
			break;
		}

		CurrentMessage.Update();

		// Render
		BeginDrawing();
		ClearBackground(GameColors::BACKGROUND);
		DrawTexture(background, 0, 0, WHITE);

		RenderGameState(MainPlayer, MainEnemy, RoundNumber, CurrentMessage);

		if (CurrentState == GameState::Battle)
		{
			DrawText(
				"1.Attack  2.Parry  3.Defend  4.Rest",
				UILayout_Constants::TEXT_X,
				UILayout_Constants::ACTION_MENU_Y,
				UILayout_Constants::TEXT_SIZE, GameColors::SUCCESS
			);
		}
		else if ((CurrentState == GameState::GameWon || CurrentState == GameState::GameOver) && !CurrentMessage.IsActive())
		{
			DrawText(
				"Press any key to exit...",
				UILayout_Constants::TEXT_X,
				UILayout_Constants::ACTION_MENU_Y,
				UILayout_Constants::TEXT_SIZE, GameColors::TEXT
			);
		}

		EndDrawing();

		// Exit on key press after end-game message finishes
		if ((CurrentState == GameState::GameWon || CurrentState == GameState::GameOver)
			&& !CurrentMessage.IsActive() && GetKeyPressed() != 0)
		{
			break;
		}
	}

	UnloadTexture(background);
	CloseWindow();
	return 0;
}

CombatOutcome BuildOutcome(CombatOutcomeType Type, const Player& MainPlayer, const Enemy& MainEnemy)
{
	switch (Type)
	{
	case CombatOutcomeType::Clash:
		return {GameMessage("Clash!", "Both warriors exchange blows!"),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::ParriedByEnemy:
		return {GameMessage(MainEnemy.GetName() + " parries the attack!", "", "", GameMessage::Type::Error),
			[](Player& P, const Enemy& E) { P.UpdateHealth(-(P.GetAttackPower() - E.GetArmor())); }};

	case CombatOutcomeType::BlockedByEnemy:
		return {GameMessage(MainEnemy.GetName() + " blocks the attack!", "Reduced damage!", "", GameMessage::Type::Warning),
			[](const Player& P, Enemy& E) { E.UpdateHealth(-((P.GetAttackPower() - E.GetArmor()) / 2)); }};

	case CombatOutcomeType::HitEnemy:
		return {GameMessage(MainEnemy.GetName() + " is caught off guard!", "Direct hit!", "", GameMessage::Type::Success),
			[](const Player& P, Enemy& E) { E.UpdateHealth(-(P.GetAttackPower() - E.GetArmor())); }};

	case CombatOutcomeType::ParriedByPlayer:
		return {GameMessage(MainPlayer.GetName() + " parries!", "", "", GameMessage::Type::Success),
			[](const Player& P, Enemy& E) { E.UpdateHealth(-(E.GetAttackPower() - P.GetArmor())); }};

	case CombatOutcomeType::Deadlock:
		return {GameMessage("Deadlock!", "Neither lands a blow."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::StandoffParryDefend:
		return {GameMessage("Tense standoff.", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::ParryRest:
		return {GameMessage(MainEnemy.GetName() + " gathers strength while " + MainPlayer.GetName() + " tries to thwart an attack!", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::BlockedByPlayer:
		return {GameMessage(MainPlayer.GetName() + " braces for impact!", "Reduced damage!", "", GameMessage::Type::Warning),
			[](Player& P, const Enemy& E) { P.UpdateHealth(-((E.GetAttackPower() - P.GetArmor()) / 2)); }};

	case CombatOutcomeType::DefendParry:
		return {GameMessage("Mutual defense.", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::BothDefend:
		return {GameMessage("Both prepare defenses.", "A stalemate ensues."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::DefendRest:
		return {GameMessage(MainPlayer.GetName() + " prepares to defend while " + MainEnemy.GetName() + " is resting!", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::HitPlayer:
		return {GameMessage(MainPlayer.GetName() + " is caught resting!", "Direct hit!", "", GameMessage::Type::Error),
			[](Player& P, const Enemy& E) { P.UpdateHealth(-(E.GetAttackPower() - P.GetArmor())); }};

	case CombatOutcomeType::RestParry:
		return {GameMessage(MainPlayer.GetName() + " gathers strength while " + MainEnemy.GetName() + " tries to thwart an attack!", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::RestDefend:
		return {GameMessage(MainPlayer.GetName() + " gathers strength while " + MainEnemy.GetName() + " prepares to defend!", "Nothing happens."),
			[](Player&, Enemy&) {}};

	case CombatOutcomeType::BothRest:
		return {GameMessage("Both warriors rest!", "Respite in battle."),
			[](Player&, Enemy&) {}};
	}
	
	return {GameMessage("..."), [](Player&, Enemy&) {}};
}

void ProcessCharacterActions(
	Player& MainPlayer,
	Enemy& MainEnemy,
	GameMessage& Message)
{
	if (TIME_SINCE_LAST_INPUT < InputCooldown) return; // Debounce: ignore input until cooldown has elapsed
	CharacterAction PlayerAction = MainPlayer.ChooseAction();
	if (PlayerAction == CharacterAction::None) return;
	CharacterAction EnemyAction = MainEnemy.ChooseAction();
	TIME_SINCE_LAST_INPUT = 0.0f; // Reset input timer on valid action

	// Check stamina before consuming it
	if (MainPlayer.GetStamina() < -Player::GetStaminaConsumption(PlayerAction))
	{
		Message = GameMessage(MainPlayer.GetName() + " is too exhausted and must rest!");
		PlayerAction = CharacterAction::Rest;
	}

	if (MainEnemy.GetStamina() < -Enemy::GetStaminaConsumption(EnemyAction))
	{
		Message = GameMessage(MainEnemy.GetName() + " is too exhausted and must rest!");
		EnemyAction = CharacterAction::Rest;
	}
	
	// Apply stamina cost after validation
	MainPlayer.UpdateStamina(Player::GetStaminaConsumption(PlayerAction));
	MainEnemy.UpdateStamina(Enemy::GetStaminaConsumption(EnemyAction));

	const auto it = OutcomeTypeMap.find({PlayerAction, EnemyAction});
	if (it == OutcomeTypeMap.end()) return;

	CombatOutcome Outcome = BuildOutcome(it->second, MainPlayer, MainEnemy);
	Message = Outcome.Message;
	Outcome.ResolveEffects(MainPlayer, MainEnemy);
}

void RenderGameState(
	const Player& MainPlayer,
	const Enemy& MainEnemy,
	int RoundNumber,
	const GameMessage& Message)
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
				UILayout_Constants::TEXT_X,
				UILayout_Constants::MESSAGE_LINE1_Y,
				UILayout_Constants::TEXT_SIZE,
				Message.GetColor()
			);
		if (!Message.Line2.empty())
			DrawText(
				Message.Line2.c_str(),
				UILayout_Constants::TEXT_X,
				UILayout_Constants::MESSAGE_LINE2_Y,
				UILayout_Constants::TEXT_SIZE,
				Message.GetColor()
			);
		if (!Message.Line3.empty())
			DrawText(
				Message.Line3.c_str(),
				UILayout_Constants::TEXT_X,
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
