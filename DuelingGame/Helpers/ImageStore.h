#pragma once
#include <unordered_map>
#include "SpriteAnimation.h"

namespace ImageStore
{
    static const char* Background = "./SourceArt/Arena.png";

    // Sprite configs indexed by SpriteState: Rest, Attack, Parry, Defend, Hurt, Die
    static const std::unordered_map<SpriteState, SpriteSheetConfig> KnightSpriteMap = {
        {SpriteState::Attack, {"./SourceArt/Characters/Knight/Attack.png", 1, 5, 5}},
        {SpriteState::Defend, {"./SourceArt/Characters/Knight/Defend.png", 1, 5, 5}},
        {SpriteState::Die, {"./SourceArt/Characters/Knight/Dead.png", 1, 6, 6}},
        {SpriteState::Hurt, {"./SourceArt/Characters/Knight/Hurt.png", 1, 2, 2}},
        {SpriteState::Parry, {"./SourceArt/Characters/Knight/Parry.png", 1, 4, 4}},
        {SpriteState::Rest, {"./SourceArt/Characters/Knight/Idle.png", 1, 4, 4}}
    };
    
    static const std::unordered_map<std::pair<EnemyType, SpriteState>, SpriteSheetConfig> EnemySpriteMap = {
        {{EnemyType::SkeletonSpearman, SpriteState::Attack}, {"./SourceArt/Characters/Skeleton-Spearman/Attack.png", 1,4, 4}},
        {{EnemyType::SkeletonSpearman, SpriteState::Defend}, {"./SourceArt/Characters/Skeleton-Spearman/Defend.png", 1, 2, 2}},
        {{EnemyType::SkeletonSpearman, SpriteState::Die}, {"./SourceArt/Characters/Skeleton-Spearman/Dead.png", 1, 5, 5}},
        {{EnemyType::SkeletonSpearman, SpriteState::Hurt}, {"./SourceArt/Characters/Skeleton-Spearman/Hurt.png", 1, 3, 3}},
        {{EnemyType::SkeletonSpearman, SpriteState::Parry}, {"./SourceArt/Characters/Skeleton-Spearman/Parry.png", 1, 4, 4}},
        {{EnemyType::SkeletonSpearman, SpriteState::Rest}, {"./SourceArt/Characters/Skeleton-Spearman/Idle.png", 1, 7, 7}},

        {{EnemyType::SkeletonWarrior, SpriteState::Attack}, {"./SourceArt/Characters/Skeleton-Warrior/Attack.png", 1, 5, 5}},
        {{EnemyType::SkeletonWarrior, SpriteState::Defend}, {"./SourceArt/Characters/Skeleton-Warrior/Defend.png", 1, 1, 1}},
        {{EnemyType::SkeletonWarrior, SpriteState::Die}, {"./SourceArt/Characters/Skeleton-Warrior/Dead.png", 1, 4, 4}},
        {{EnemyType::SkeletonWarrior, SpriteState::Hurt}, {"./SourceArt/Characters/Skeleton-Warrior/Hurt.png", 1, 2, 2}},
        {{EnemyType::SkeletonWarrior, SpriteState::Parry}, {"./SourceArt/Characters/Skeleton-Warrior/Parry.png", 1, 6, 6}},
        {{EnemyType::SkeletonWarrior, SpriteState::Rest}, {"./SourceArt/Characters/Skeleton-Warrior/Idle.png", 1, 7, 7}},

        {{EnemyType::Viking, SpriteState::Attack}, {"./SourceArt/Characters/Viking/Attack.png", 1, 4, 4}},
        {{EnemyType::Viking, SpriteState::Defend}, {"./SourceArt/Characters/Viking/Defend.png", 1, 3, 3}},
        {{EnemyType::Viking, SpriteState::Die}, {"./SourceArt/Characters/Viking/Dead.png", 1, 4, 4}},
        {{EnemyType::Viking, SpriteState::Hurt}, {"./SourceArt/Characters/Viking/Hurt.png", 1, 2, 2}},
        {{EnemyType::Viking, SpriteState::Parry}, {"./SourceArt/Characters/Viking/Parry.png", 1, 3, 3}},
        {{EnemyType::Viking, SpriteState::Rest}, {"./SourceArt/Characters/Viking/Idle.png", 1, 5, 5}},

        {{EnemyType::NormanWarrior, SpriteState::Attack}, {"./SourceArt/Characters/Norman-Warrior/Attack.png", 1, 4, 4}},
        {{EnemyType::NormanWarrior, SpriteState::Defend}, {"./SourceArt/Characters/Norman-Warrior/Defend.png", 1, 2, 2}},
        {{EnemyType::NormanWarrior, SpriteState::Die}, {"./SourceArt/Characters/Norman-Warrior/Dead.png", 1, 4, 4}},
        {{EnemyType::NormanWarrior, SpriteState::Hurt}, {"./SourceArt/Characters/Norman-Warrior/Hurt.png", 1, 3, 3}},
        {{EnemyType::NormanWarrior, SpriteState::Parry}, {"./SourceArt/Characters/Norman-Warrior/Parry.png", 1, 4, 4}},
        {{EnemyType::NormanWarrior, SpriteState::Rest}, {"./SourceArt/Characters/Norman-Warrior/Idle.png", 1, 5, 5}}
    };
    
    static SpriteSheetConfig GetEnemySpriteSheetConfig(EnemyType Type, SpriteState State)
    {
        auto it = ImageStore::EnemySpriteMap.find({Type, State});
        if (it != ImageStore::EnemySpriteMap.end())
            return it->second;
        else
            return {"", 0, 0, 0}; // Return an empty config if not found
    }
};

