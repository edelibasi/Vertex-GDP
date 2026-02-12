#pragma once
#include <raylib.h>

struct GameColors
{
	static constexpr Color BACKGROUND = BLACK;
	static constexpr Color DAMAGE = RED;
	static constexpr Color SUCCESS = GREEN;
	static constexpr Color TEXT = LIGHTGRAY;
	static constexpr Color WARNING = YELLOW;
};

struct GameConstants
{
	static constexpr int TARGET_FPS = 60;
	static constexpr int MAX_ROUNDS = 5;
	static constexpr int MESSAGE_DISPLAY_TIME = 180; // frames at 60 FPS = 2 seconds
};

// Layout constants organized in struct
struct UILayout_Constants
{
	// View Sizes
	static constexpr int SCREEN_WIDTH = 800;
	static constexpr int SCREEN_HEIGHT = 600;
	
	// Background
	static constexpr int BACKGROUND_WIDTH = SCREEN_WIDTH;
	static constexpr int BACKGROUND_HEIGHT = 400;

	// Text positioning
	static constexpr int TEXT_SIZE = 20;
	static constexpr int TEXT_SIZE_SMALL = TEXT_SIZE - 2;
	static constexpr int TEXT_X = 20;
	static constexpr int TEXT_X_CENTER = 190;

	// Title & Round
	static constexpr int TITLE_Y = 420;
	static constexpr int ROUND_Y = 450;
	static constexpr int ACTION_MENU_Y = ROUND_Y + 30;

	// Messages
	static constexpr int MESSAGE_Y_START = 500;
	static constexpr int MESSAGE_Y_SPACING = 20;
	static constexpr int MESSAGE_LINE1_Y = MESSAGE_Y_START;
	static constexpr int MESSAGE_LINE2_Y = MESSAGE_Y_START + MESSAGE_Y_SPACING;
	static constexpr int MESSAGE_LINE3_Y = MESSAGE_Y_START + (MESSAGE_Y_SPACING * 2);

	// Character Stats
	static constexpr int STAT_X = 50;
	static constexpr int STAT_X_ENEMY = STAT_X + 400;
	static constexpr int STAT_Y_START = 320;
	static constexpr int STAT_Y_SPACING = 25;

	// Sprite Rendering
	static constexpr int PLAYER_SPRITE_X = 120;
	static constexpr int ENEMY_SPRITE_X = 500;
	static constexpr int SPRITE_GROUND_Y = 350;
	static constexpr float SPRITE_DISPLAY_HEIGHT = 150.0f;
};