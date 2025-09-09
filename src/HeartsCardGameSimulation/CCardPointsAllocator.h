#pragma once
#include "AppEnumsConsts.h"
#include "CCard.h"

class CCardPointsAllocator
{
public:
	CCardPointsAllocator() = default;
	static int GetPoints(CARD_SUIT suit, CARD_RANK rank);
};

