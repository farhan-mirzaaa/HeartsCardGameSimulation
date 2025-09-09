#include "CCardsPassDirection.h"

CCardsPassDirection::CCardsPassDirection()
{
}

CCardsPassDirection::CCardsPassDirection(CARDS_PASSING_DIRECTION direction) : m_direction(direction)
{
}

CARDS_PASSING_DIRECTION CCardsPassDirection::Direction()
{
    return m_direction;
}

std::string CCardsPassDirection::GetString()
{
	return CCardsPassDirection::to_string(m_direction);
}

std::string CCardsPassDirection::to_string(CARDS_PASSING_DIRECTION direction)
{
	switch (direction)
	{
	case CARDS_PASSING_DIRECTION::LEFT:
		return "LEFT";
	case CARDS_PASSING_DIRECTION::RIGHT:
		return "RIGHT";
	case CARDS_PASSING_DIRECTION::OPPOSITE:
		return "OPPOSITE";
	case CARDS_PASSING_DIRECTION::NONE:
		return "NONE";
	default:
		return "NONE";
	}
}
