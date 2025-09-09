#pragma once
#include <vector>
#include "CRound.h"
#include "CPlayerManager.h"
#include "CCardsManager.h"

class CGame
{
private:
	CPlayerManager m_playerManager{};
	CCardsManager m_cardsManager{};

	std::vector<CRound> m_vecRounds{};

	bool m_isGameEnded{ false };

	void CreateNewRound();
	void ExecuteRound();
public:
	CGame();
	~CGame();
	void Initialize();
	void Run();
};

