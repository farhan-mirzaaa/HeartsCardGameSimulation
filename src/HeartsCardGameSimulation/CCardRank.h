#pragma once
#include "AppEnumsConsts.h"
#include <string>

class CCardRank
{
private:
	CARD_RANK m_rank{};
	std::string m_str{};

public:
	CCardRank() = default;
	CCardRank(CARD_RANK rank);

	std::string GetString();
	CARD_RANK Rank();

	bool operator<(const CCardRank& other);
	bool operator==(const CCardRank& other);
};

