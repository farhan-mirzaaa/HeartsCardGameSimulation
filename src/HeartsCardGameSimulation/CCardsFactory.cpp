#include "CCardsFactory.h"

CCard CCardsFactory::CreateCardObject(CARD_SUIT suit, CARD_RANK rank)
{
    CCardSuit cardSuit{ suit };
    CCardRank cardRank{ rank };

    return CCard(cardSuit, cardRank, CCardPointsAllocator::GetPoints(suit, rank));
}
