#pragma once
#include <memory>
#include <vector>
#include "CCard.h"

class CScoreCalculator
{
private:
	CScoreCalculator();
public:
	static int CalculateScore(std::vector<CCard> takenCards);
	static int CalculateScore(bool haveAllHeartsAndQueenOfSpades);
	static int GetMaxLooserScore();
};

