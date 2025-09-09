#include "CCardsManager.h"
#include "AppEnumsConsts.h"
#include "CCardsFactory.h"
#include <algorithm>
#include <random>

CCardsManager::CCardsManager()
{

}

void CCardsManager::CreateCards()
{
	for (int k = 0; k < CARD_SUITS; k++)
	{
		for (int i = 1; i <= MAX_CARDS_IN_SUIT; i++)
		{
			m_vecCards.push_back(std::move(CCardsFactory::CreateCardObject(
				static_cast<CARD_SUIT>(k), static_cast<CARD_RANK>(i+1))));
		}
	}
}

void CCardsManager::ShuffleCards(int times)
{
	//std::random_shuffle(m_vecCards.begin(), m_vecCards.end());

	std::random_device rd;   // Provides a non-deterministic seed
	std::mt19937 g(rd());    // Mersenne Twister engine seeded with rd

	for(int i=0; i< times;i++)
		std::shuffle(m_vecCards.begin(), m_vecCards.end(), g);
}

void CCardsManager::DistributeCards(std::vector<std::shared_ptr<CPlayer>>& players)
{
	int cardCounter{};
	for (auto& p : players)
	{
		for (int i = 0; i < MAX_CARDS_IN_SUIT; i++)
		{
			(*p).CollectCardInHand(m_vecCards[cardCounter++]);
		}
	}
	m_vecCards.clear();
}

void CCardsManager::RetreiveCards(std::vector<std::shared_ptr<CPlayer>>& players)
{
	for (auto& p : players)
	{
		auto vecCards = p->ReturnAllTakenCards();
		if (vecCards.size() > 0)
		{
			for (auto c : vecCards)
			{
				m_vecCards.emplace_back(c);
			}
		}
	}
}
