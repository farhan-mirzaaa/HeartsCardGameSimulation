#pragma once
#include <vector>
#include "CCard.h"
#include <memory>
#include "CPlayer.h"

class CCardsManager
{
private:
	std::vector<CCard> m_vecCards{};
public:
	CCardsManager();

	void CreateCards();
	void ShuffleCards(int times);

	void DistributeCards(std::vector<std::shared_ptr<CPlayer>>& players);
	void RetreiveCards(std::vector<std::shared_ptr<CPlayer>>& players);
};

