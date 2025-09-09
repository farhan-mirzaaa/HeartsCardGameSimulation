#include "CCardPointsAllocator.h"

int CCardPointsAllocator::GetPoints(CARD_SUIT suit, CARD_RANK rank)
{
	switch (suit)
	{
	case CARD_SUIT::SPADES:
		if (rank == CARD_RANK::QUEEN)
			return 13;
		break;
	case CARD_SUIT::CLUBS:
		break;
	case CARD_SUIT::HEARTS:
		return 1;
		break;
	case CARD_SUIT::DIAMONDS:
		break;
	default:
		break;
	}

	return 0;
}
