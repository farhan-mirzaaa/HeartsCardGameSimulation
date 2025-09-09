#pragma once
#include "CScores.h"
#include <string>
#include <vector>
#include "CPlayer.h"
#include "CPlayerManager.h"

class CRound
{
	static int g_nextNumber;
private:
	int m_number{};
	int m_currentTrickNumber{};
	
	bool m_bIsCompleted{ false };
	CARDS_PASSING_DIRECTION m_cardsPassingDirection{ CARDS_PASSING_DIRECTION::LEFT};
	
	std::vector<CScores> m_vecPlayerScores;
public:
	CRound();

	int GetRoundNumber();
	bool IsRoundCompleted();
	CARDS_PASSING_DIRECTION GetPassDirection();
	void RecordScores(const std::vector<std::shared_ptr<CPlayer>>& vecPlayers);
	void PassCards(std::vector<std::shared_ptr<CPlayer>>& players);

	void ExecuteRound(CPlayerManager& pManager);
	std::string ExecuteTrick(CPlayerManager& pManager);
	void EndRound(CPlayerManager& pManager);

	std::string GetString();

};

