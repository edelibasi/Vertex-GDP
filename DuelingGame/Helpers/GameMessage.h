#pragma once
#include <cstdint>
#include <string>
#include "UILayout+Constants.h"

struct GameMessage
{
	enum class Type: std::uint8_t { Default, Success, Warning, Error };

	GameMessage() : FrameCount(0), MessageType(Type::Default) {}
	GameMessage(
		std::string L1,
		std::string L2 = "",
		std::string L3 = "",
		const Type MessageType = Type::Default
	)
		: Line1(std::move(L1)), Line2(std::move(L2)), Line3(std::move(L3)), FrameCount(GameConstants::MESSAGE_DISPLAY_TIME), MessageType(MessageType) { }
	
	std::string Line1;
	std::string Line2;
	std::string Line3;
	
	bool IsActive() const { return FrameCount > 0; }
	void Update() { if (FrameCount > 0) --FrameCount; }
	Color GetColor() const;
	
protected:
    int FrameCount;
    Type MessageType;
};
