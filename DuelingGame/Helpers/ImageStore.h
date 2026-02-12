#pragma once
#include <string>
#include "SpriteAnimation.h"

namespace ImageStore
{
    static const std::string Background = "./SourceArt/Arena.png";

    // Sprite configs indexed by SpriteState: Rest, Attack, Parry, Defend, Hurt, Die
    static const CharacterSpriteConfig KnightSprites = {{
        {"./SourceArt/Characters/Knight/KNIGHT-REST.png",    7, 1,  7},
        {"./SourceArt/Characters/Knight/KNIGHT-ATTACK.png",  6, 1,  6},
        {"./SourceArt/Characters/Knight/KNIGHT-PARRY.png",   5, 1,  5},
        {"./SourceArt/Characters/Knight/KNIGHT-DEFEND.png",  6, 1,  6},
        {"./SourceArt/Characters/Knight/KNIGHT-HURT.png",    4, 1,  4},
        {"./SourceArt/Characters/Knight/KNIGHT-DIE.png",    10, 1, 10}
    }};

    static const CharacterSpriteConfig GoblinSprites = {{
        {"./SourceArt/Characters/Goblin/GOBLIN-REST.png",    3, 3,  9},
        {"./SourceArt/Characters/Goblin/GOBLIN-ATTACK.png",  4, 3, 11},
        {"./SourceArt/Characters/Goblin/GOBLIN-PARRY.png",   4, 3, 10},
        {"./SourceArt/Characters/Goblin/GOBLIN-DEFEND.png",  3, 3,  9},
        {"./SourceArt/Characters/Goblin/GOBLIN-HURT.png",    2, 2,  4},
        {"./SourceArt/Characters/Goblin/GOBLIN-DIE.png",     4, 3, 11}
    }};

    static const CharacterSpriteConfig GoblinWarriorSprites = {{
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-REST.png",    3, 3,  9},
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-ATTACK.png",  4, 3, 11},
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-PARRY.png",   4, 3, 10},
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-DEFEND.png",  3, 3,  9},
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-HURT.png",    2, 2,  4},
        {"./SourceArt/Characters/Goblin-Warrior/GOBLIN-WARRIOR-DIE.png",     4, 3, 11}
    }};

    static const CharacterSpriteConfig GoblinBossSprites = {{
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-REST.png",    6, 3, 18},
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-ATTACK.png",  6, 4, 24},
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-PARRY.png",   6, 4, 24},
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-DEFEND.png",  6, 3, 18},
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-HURT.png",    6, 3, 18},
        {"./SourceArt/Characters/Goblin-Boss/GOBLIN-BOSS-DIE.png",     3, 3,  9}
    }};

    static const CharacterSpriteConfig GoblinGiantSprites = {{
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-REST.png",    5, 3, 15},
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-ATTACK.png",  6, 4, 22},
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-PARRY.png",   6, 4, 22},
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-DEFEND.png",  5, 4, 20},
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-HURT.png",    5, 4, 20},
        {"./SourceArt/Characters/Goblin-Giant/GOBLIN-GIANT-DIE.png",     5, 3, 13}
    }};

    // Enemy sprite config per round (1-indexed, index 0 unused)
    static const CharacterSpriteConfig* EnemySpritesByRound[] = {
        nullptr,              // Round 0 (unused)
        &GoblinSprites,       // Round 1: Goblin
        &GoblinWarriorSprites,// Round 2: Goblin Warrior
        &GoblinBossSprites,   // Round 3: Gladiator
        &GoblinGiantSprites,  // Round 4: Berserker
        &KnightSprites        // Round 5: Knight Champion
    };
};
