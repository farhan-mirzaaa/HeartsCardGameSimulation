#pragma once
#include "CHumanPlayer.h"
#include "CComputerPlayer.h"
#include "AppEnumsConsts.h"
#include <memory>

class CPlayerFactory
{
public:
	static std::shared_ptr<CPlayer> CreatePlayerObject(
		PLAYER_TYPE type, PLAYER_POSITION position, std::string name = "");
};

