#pragma once

#include <map>

#include "SpriteAnimation.h"

namespace ImageStore
{
    static const char* Background = "./SourceArt/Arena.png";

    // Sprite configs indexed by SpriteState: Rest, Attack, Parry, Defend, Hurt, Die
    static const CharacterSpriteConfig KnightSprites = {
        {
            {"./SourceArt/Characters/Knight/Attack.png", 1, 5, 5},
            {"./SourceArt/Characters/Knight/Defend.png", 1, 5, 5},
            {"./SourceArt/Characters/Knight/Dead.png", 1, 6, 6},
            {"./SourceArt/Characters/Knight/Hurt.png", 1, 2, 2},
            {"./SourceArt/Characters/Knight/Parry.png", 1, 4, 4},
            {"./SourceArt/Characters/Knight/Idle.png", 1, 4, 4}
        }
    };

    static const CharacterSpriteConfig SkeletonSpearmanSprites = {
        {
            {"./SourceArt/Characters/Skeleton-Spearman/Attack.png", 1,4, 4},
            {"./SourceArt/Characters/Skeleton-Spearman/Defend.png", 1, 2, 2},
            {"./SourceArt/Characters/Skeleton-Spearman/Dead.png", 1, 5, 5},
            {"./SourceArt/Characters/Skeleton-Spearman/Hurt.png", 1, 3, 3},
            {"./SourceArt/Characters/Skeleton-Spearman/Parry.png", 1, 4, 4},
            {"./SourceArt/Characters/Skeleton-Spearman/Idle.png", 1, 7, 7}
        }
    };
    
    static const CharacterSpriteConfig SkeletonWarriorSprites = {
        {
            {"./SourceArt/Characters/Skeleton-Warrior/Attack.png", 1, 5, 5},
            {"./SourceArt/Characters/Skeleton-Warrior/Defend.png", 1, 1, 1},
            {"./SourceArt/Characters/Skeleton-Warrior/Dead.png", 1, 4, 4},
            {"./SourceArt/Characters/Skeleton-Warrior/Hurt.png", 1, 2, 2},
            {"./SourceArt/Characters/Skeleton-Warrior/Parry.png", 1, 6, 6},
            {"./SourceArt/Characters/Skeleton-Warrior/Idle.png", 1, 7, 7}
        }
    };
    
    static const CharacterSpriteConfig VikingSprites = {
        {
            {"./SourceArt/Characters/Viking/Attack.png", 1, 4, 4},
            {"./SourceArt/Characters/Viking/Defend.png", 1, 3, 3},
            {"./SourceArt/Characters/Viking/Dead.png", 1, 4, 4},
            {"./SourceArt/Characters/Viking/Hurt.png", 1, 2, 2},
            {"./SourceArt/Characters/Viking/Parry.png", 1, 3, 3},
            {"./SourceArt/Characters/Viking/Idle.png", 1, 5, 5}
        }
    };
    
    static const CharacterSpriteConfig NormanWarriorSprites = {
        {
            {"./SourceArt/Characters/Norman-Warrior/Attack.png", 1, 4, 4},
            {"./SourceArt/Characters/Norman-Warrior/Defend.png", 1, 2, 2},
            {"./SourceArt/Characters/Norman-Warrior/Dead.png", 1, 4, 4},
            {"./SourceArt/Characters/Norman-Warrior/Hurt.png", 1, 3, 3},
            {"./SourceArt/Characters/Norman-Warrior/Parry.png", 1, 4, 4},
{"./SourceArt/Characters/Norman-Warrior/Idle.png", 1, 5, 5}
        }
    };
    
    // Enemy sprite config per round (1-indexed, index 0 unused)
    static const CharacterSpriteConfig* EnemySpritesByRound[] = {
        nullptr,                     // Round 0 (unused)
        &SkeletonSpearmanSprites,    // Round 1: Skeleton Spearman
        &SkeletonWarriorSprites,     // Round 2: Skeleton Warrior
        &VikingSprites,              // Round 3: Viking
        &NormanWarriorSprites,       // Round 4: Norman Warrior
    };
};

