#pragma once

#include <string>
#include "CCardSuit.h"
#include "CCardRank.h"


class CCard
{
private:
	CCardSuit m_suit;
	CCardRank m_rank;
	int	m_points{};

public:
	CCard();
	CCard(CCardSuit suit, CCardRank rank, int points);

	std::string GetString();
	CCardSuit GetSuit();
	CCardRank GetRank();

	bool operator<(const CCard& other);
	bool operator==(const CCard& other);
};

