#include "CCardSuit.h"

CCardSuit::CCardSuit(CARD_SUIT suit) : m_suit(suit)
{
	switch (suit)
	{
	case CARD_SUIT::SPADES:
		m_str = "SPADES";
		break;
	case CARD_SUIT::CLUBS:
		m_str = "CLUBS";
		break;
	case CARD_SUIT::HEARTS:
		m_str = "HEARTS";
		break;
	case CARD_SUIT::DIAMONDS:
		m_str = "DIAMONDS";
		break;
	}
}

std::string CCardSuit::GetString()
{
	return m_str;
}

CARD_SUIT CCardSuit::Suit()
{
	return m_suit;
}

bool CCardSuit::operator==(const CCardSuit& other)
{
	return (m_suit == other.m_suit);
}

bool CCardSuit::operator!=(const CCardSuit& other)
{
	return (m_suit != other.m_suit);
}

bool CCardSuit::operator<(const CCardSuit& other)
{
	return this->m_suit < other.m_suit;
}
