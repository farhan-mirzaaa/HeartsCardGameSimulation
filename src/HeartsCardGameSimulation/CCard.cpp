#include "CCard.h"

CCard::CCard()
{

}

CCard::CCard(CCardSuit suit, CCardRank rank, int points) : m_suit(suit),
m_rank(rank),
m_points(points)
{
}

CCardSuit CCard::GetSuit()
{
	return m_suit;
}

CCardRank CCard::GetRank()
{
	return m_rank;
}

std::string CCard::GetString()
{
	return (m_suit.GetString() + "-" + m_rank.GetString());
}

bool CCard::operator<(const CCard& other)
{
	if (m_suit != other.m_suit) {
		return m_suit < other.m_suit;
	}
	return m_rank < other.m_rank;
}

bool CCard::operator==(const CCard& other)
{
	if (m_suit == other.m_suit && m_rank == other.m_rank)
		return true;
	return false;
}
