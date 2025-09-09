#include "CCardRank.h"

CCardRank::CCardRank(CARD_RANK rank): m_rank(rank)
{
	switch (rank)
	{
	case CARD_RANK::TWO:
		m_str = "2";
		break;
	case CARD_RANK::THREE:
		m_str = "3";
		break;
	case CARD_RANK::FOUR:
		m_str = "4";
		break;
	case CARD_RANK::FIVE:
		m_str = "5";
		break;
	case CARD_RANK::SIX:
		m_str = "6";
		break;
	case CARD_RANK::SEVEN:
		m_str = "7";
		break;
	case CARD_RANK::EIGHT:
		m_str = "8";
		break;
	case CARD_RANK::NINE:
		m_str = "9";
		break;
	case CARD_RANK::TEN:
		m_str = "10";
		break;
	case CARD_RANK::JACK:
		m_str = "J";
		break;
	case CARD_RANK::QUEEN:
		m_str = "Q";
		break;
	case CARD_RANK::KING:
		m_str = "K";
		break;
	case CARD_RANK::ACE:
		m_str = "A";
		break;
	default:
		break;
	}
}

std::string CCardRank::GetString()
{
	return m_str;
}

CARD_RANK CCardRank::Rank()
{
	return m_rank;
}

bool CCardRank::operator<(const CCardRank& other)
{
	return m_rank < other.m_rank;
}

bool CCardRank::operator==(const CCardRank& other)
{
	return m_rank == other.m_rank;
}
