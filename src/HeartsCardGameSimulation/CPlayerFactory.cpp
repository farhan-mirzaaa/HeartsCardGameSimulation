#include "CPlayerFactory.h"

std::shared_ptr<CPlayer> CPlayerFactory::CreatePlayerObject(
	PLAYER_TYPE playerType, PLAYER_POSITION position, std::string name)
{
	switch (playerType)
	{
	case PLAYER_TYPE::HUMAN:
		return std::make_shared<CHumanPlayer>(name, position);
	case PLAYER_TYPE::COMPUTER:
		return std::make_shared<CComputerPlayer>(position);
	}
	return nullptr;
}
