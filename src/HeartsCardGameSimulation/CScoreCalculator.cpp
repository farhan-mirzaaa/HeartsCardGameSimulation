#include "CScoreCalculator.h"

CScoreCalculator::CScoreCalculator()
{}

int CScoreCalculator::CalculateScore(std::vector<CCard> takenCards)
{
	int score{ 0 };
	for (auto c : takenCards)
	{
		if ((c.GetSuit().Suit() == CARD_SUIT::SPADES)
			&& (c.GetRank().Rank() == CARD_RANK::QUEEN))
			score += 13;
		else if (c.GetSuit().Suit() == CARD_SUIT::HEARTS)
			score += 1;
	}
	return score;
}

int CScoreCalculator::CalculateScore(bool haveAllHeartsAndQueenOfSpades)
{
	return 26;
}

int CScoreCalculator::GetMaxLooserScore()
{
	return 100;
}
