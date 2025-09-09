#pragma once

#include "CHumanPlayer.h"
#include "CComputerPlayer.h"
#include <vector>
#include <string>

class CPlayerManager
{
private:
	std::vector<std::shared_ptr<CPlayer>> m_vecPlayers{};

public:
	void CreatePlayers(int numTotalPlayers, int numHumanPlayers);

	int GetNumberOfPlayers();
	std::vector<std::shared_ptr<CPlayer>>& GetPlayers();

	void SetLead(std::string playerName);
	std::string GetLeadName();
	std::string GetIsAnyPlayerHaveAllHeartsAndQueenOfSpades();
	std::pair<std::string, int> IsAnyPlayerLost();

	void HandoverTrickCardsToLooser(std::string playerName, std::vector<CCard> trickCards);

};

