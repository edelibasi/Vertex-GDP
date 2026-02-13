#pragma once

#include <string>
#include "raylib.h"

enum class SpriteState : uint8_t
{
    Rest,
    Attack,
    Parry,
    Defend,
    Hurt,
    Die,
    Idle
};

struct SpriteAnimation
{
    Texture2D Sheet;
    int Rows;
    int Columns;
    int CurrentFrame;
    int TotalFrames;
    int FrameCounter; // Counts frames for timing
    int FrameSpeed; // Frames to wait before advancing to the next frame
    bool Looping = false;
    bool Playing = false;
    
    float FrameWidth() const { return static_cast<float>(Sheet.width) / Columns; }
    float FrameHeight() const { return static_cast<float>(Sheet.height) / Rows; }
    
    Rectangle GetSourceRect() const
    {
        int Col = CurrentFrame % Columns;
        int Row = CurrentFrame / Columns;
        return { Col * FrameWidth(), Row * FrameHeight(), FrameWidth(), FrameHeight() };
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
    
    void Unload()
    {
        if (Sheet.id != 0) UnloadTexture(Sheet);
        Sheet = {};
    }
};

struct SpriteSheetConfig {
    const char* ImagePath;
    int Rows;
    int Columns;
    int FrameCount;
};