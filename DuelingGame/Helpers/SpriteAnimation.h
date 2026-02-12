#pragma once
#include <raylib.h>

enum class SpriteState : uint8_t
{
	Rest,
	Attack,
	Parry,
	Defend,
	Hurt,
	Die,
	Count
};

struct SpriteAnimation
{
	Texture2D Sheet = {};
	int Columns = 1;
	int Rows = 1;
	int TotalFrames = 1;
	int CurrentFrame = 0;
	int FrameCounter = 0;
	int FrameSpeed = 8;
	bool Looping = true;
	bool Playing = false;

	float FrameWidth() const { return static_cast<float>(Sheet.width) / Columns; }
	float FrameHeight() const { return static_cast<float>(Sheet.height) / Rows; }

	Rectangle GetSourceRect() const
	{
		int Col = CurrentFrame % Columns;
		int Row = CurrentFrame / Columns;
		return { Col * FrameWidth(), Row * FrameHeight(), FrameWidth(), FrameHeight() };
	}

	void Update()
	{
		if (!Playing) return;
		FrameCounter++;
		if (FrameCounter >= FrameSpeed)
		{
			FrameCounter = 0;
			CurrentFrame++;
			if (CurrentFrame >= TotalFrames)
			{
				if (Looping)
					CurrentFrame = 0;
				else
				{
					CurrentFrame = TotalFrames - 1;
					Playing = false;
				}
			}
		}
	}

	void Play()
	{
		Playing = true;
		CurrentFrame = 0;
		FrameCounter = 0;
	}

	void Stop()
	{
		Playing = false;
		CurrentFrame = 0;
		FrameCounter = 0;
	}

	void Draw(Vector2 Position, float Scale = 1.0f, bool FlipH = false) const
	{
		if (Sheet.id == 0) return;
		Rectangle Source = GetSourceRect();
		if (FlipH) Source.width = -Source.width;
		Rectangle Dest = {
			Position.x, Position.y,
			FrameWidth() * Scale, FrameHeight() * Scale
		};
		DrawTexturePro(Sheet, Source, Dest, {0, 0}, 0.0f, WHITE);
	}

	void Unload()
	{
		if (Sheet.id != 0) UnloadTexture(Sheet);
		Sheet = {};
	}
};

struct SpriteSheetConfig
{
	const char* Path;
	int Columns;
	int Rows;
	int TotalFrames;
};

struct CharacterSpriteConfig
{
	SpriteSheetConfig Sheets[static_cast<int>(SpriteState::Count)];
};

struct CharacterSprites
{
	SpriteAnimation Animations[static_cast<int>(SpriteState::Count)];
	SpriteState CurrentState = SpriteState::Rest;

	SpriteAnimation& Current() { return Animations[static_cast<int>(CurrentState)]; }
	const SpriteAnimation& Current() const { return Animations[static_cast<int>(CurrentState)]; }

	void SetState(SpriteState NewState)
	{
		if (CurrentState == NewState && Current().Playing) return;
		CurrentState = NewState;
		bool ShouldLoop = (NewState == SpriteState::Rest);
		Current().Looping = ShouldLoop;
		Current().Play();
	}

	void Update() { Current().Update(); }

	void Draw(Vector2 Position, float Scale = 1.0f, bool FlipH = false) const
	{
		Current().Draw(Position, Scale, FlipH);
	}

	void LoadFromConfig(const CharacterSpriteConfig& Config)
	{
		for (int i = 0; i < static_cast<int>(SpriteState::Count); i++)
		{
			const auto& Sheet = Config.Sheets[i];
			Animations[i].Sheet = LoadTexture(Sheet.Path);
			Animations[i].Columns = Sheet.Columns;
			Animations[i].Rows = Sheet.Rows;
			Animations[i].TotalFrames = Sheet.TotalFrames;
			Animations[i].FrameSpeed = 6;
			Animations[i].Looping = (static_cast<SpriteState>(i) == SpriteState::Rest);
		}
		// Start playing Rest by default
		Animations[static_cast<int>(SpriteState::Rest)].Play();
	}

	void UnloadAll()
	{
		for (auto& Anim : Animations) Anim.Unload();
	}
};

static SpriteState ActionToSpriteState(CharacterAction Action)
{
	switch (Action)
	{
	case CharacterAction::Attack: return SpriteState::Attack;
	case CharacterAction::Parry:  return SpriteState::Parry;
	case CharacterAction::Defend: return SpriteState::Defend;
	case CharacterAction::Rest:   return SpriteState::Rest;
	default:                      return SpriteState::Rest;
	}
}
