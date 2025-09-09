#include "CPlayerManager.h"
#include "CPlayerFactory.h"
#include <algorithm>
#include "CScoreCalculator.h"

void CPlayerManager::CreatePlayers(int totalPlayers, int humans)
{
	for (int i = 1; i <= totalPlayers; i++)
	{
		PLAYER_TYPE pType{ PLAYER_TYPE::COMPUTER };
		if (humans > 0)
		{
			pType = PLAYER_TYPE::HUMAN;
			--humans;
		}
		auto player = CPlayerFactory::CreatePlayerObject(pType, (PLAYER_POSITION)i, "");
		if (player != nullptr)
			m_vecPlayers.push_back( player );
	}
}

int CPlayerManager::GetNumberOfPlayers()
{
	return static_cast<int>(m_vecPlayers.size());
}

std::vector<std::shared_ptr<CPlayer>>& CPlayerManager::GetPlayers()
{
	return m_vecPlayers;
}

void CPlayerManager::SetLead(std::string playerName)
{
	for (auto& p : m_vecPlayers)
	{
		if ((*p).GetName() == playerName)
			(*p).SetIsLead(true);
		else
			(*p).SetIsLead(false);
	}
}

void CPlayerManager::HandoverTrickCardsToLooser(std::string playerName, std::vector<CCard> trickCards)
{
	for (auto& p : m_vecPlayers)
	{
		if ((*p).GetName() == playerName)
		{
			(*p).TakeCardsAndUpdateScore(trickCards);
			break;
		}
	}
}

std::pair<std::string, int> CPlayerManager::IsAnyPlayerLost()
{
	int score{};
	std::string playerName{ "" };
	for (auto& p : m_vecPlayers)
	{
		if (p->GetScore() >= CScoreCalculator::GetMaxLooserScore())
		{
			playerName = p->GetName();
			score = p->GetScore();
		}
	}
	return std::make_pair(playerName, score);
}

std::string CPlayerManager::GetLeadName()
{
	for (auto& p : m_vecPlayers)
	{
		if (p->GetIsLead())
			return p->GetName();
	}
	return "";
}

std::string CPlayerManager::GetIsAnyPlayerHaveAllHeartsAndQueenOfSpades()
{
	for (auto& p : m_vecPlayers)
	{
		if (p->HaveAllHeartsAndQueenOfSpades())
			return p->GetName();
	}
	return "";
}