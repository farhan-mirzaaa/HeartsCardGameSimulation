#pragma once
#include "AppEnumsConsts.h"
#include <string>

class CCardSuit
{
private:
	CARD_SUIT m_suit{};
	std::string m_str{};

public:
	CCardSuit() = default;
	CCardSuit(CARD_SUIT suit);

	std::string GetString();
	CARD_SUIT Suit();

	bool operator==(const CCardSuit& other);
	bool operator!=(const CCardSuit& other);
	bool operator<(const CCardSuit& other);
};

