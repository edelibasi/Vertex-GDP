#include "GameMessage.h"

Color GameMessage::GetColor() const
{
    switch (MessageType)
        {
        case Type::Success: return GameColors::SUCCESS;
        case Type::Warning: return GameColors::WARNING;
        case Type::Error: return GameColors::DAMAGE;
        case Type::Default: return GameColors::TEXT;
        }
        return GameColors::TEXT;
};