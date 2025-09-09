#pragma once
#include "CCard.h"
#include <memory>
#include "CCardPointsAllocator.h"
#include "CCardRank.h"
#include "CCardSuit.h"

class CCardsFactory
{
public:
	CCardsFactory() = default;

	static CCard CreateCardObject(CARD_SUIT suit, CARD_RANK rank);
};

