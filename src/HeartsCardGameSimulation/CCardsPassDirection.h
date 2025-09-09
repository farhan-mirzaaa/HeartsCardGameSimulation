#pragma once
#include "AppEnumsConsts.h"
#include <string>

class CCardsPassDirection
{
private:
	CARDS_PASSING_DIRECTION m_direction{CARDS_PASSING_DIRECTION::NONE};

public:
	CCardsPassDirection();
	CCardsPassDirection(CARDS_PASSING_DIRECTION direction);

	CARDS_PASSING_DIRECTION Direction();

	std::string GetString();
	static std::string to_string(CARDS_PASSING_DIRECTION direction);
};

