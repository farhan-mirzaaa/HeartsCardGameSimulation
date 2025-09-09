#include "CPlayer.h"
#include <algorithm>
#include "CScoreCalculator.h"
#include <iterator>

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(PLAYER_POSITION position):m_postion(position),
											m_totalScore(0)
											
{
	switch (position)
	{
	case PLAYER_POSITION::NORTH:
		m_name = "NORTH_PLAYER";
		break;
	case PLAYER_POSITION::EAST:
		m_name = "EAST_PLAYER";
		break;
	case PLAYER_POSITION::SOUTH:
		m_name = "SOUTH_PLAYER";
		break;
	case PLAYER_POSITION::WEST:
		m_name = "WEST_PLAYER";
		break;
	}
}

CPlayer::CPlayer(std::string name, PLAYER_POSITION position) : m_name(name),
																m_postion(position),
																m_totalScore(0)
{
}

bool CPlayer::IsOnwerOfTwoOfClubs()
{
	for (auto& c : m_vecCardsInHand)
	{
		if (c.GetRank().Rank() == CARD_RANK::TWO &&
			c.GetSuit().Suit() == CARD_SUIT::CLUBS)
		{
			return true;
		}
	}
	return false;
}

bool CPlayer::HaveAllHeartsAndQueenOfSpades()
{
	bool haveQueenOfSpades{ false };
	int heartsCounter{ 0 };
	for (CCard c : m_vecCardsTaken)
	{
		if (c.GetSuit().Suit() == CARD_SUIT::SPADES
			&& c.GetRank().Rank() == CARD_RANK::QUEEN)
			haveQueenOfSpades = true;
		if (c.GetSuit().Suit() == CARD_SUIT::HEARTS)
			heartsCounter++;
	}

	if (haveQueenOfSpades && heartsCounter == MAX_CARDS_IN_SUIT)
		return true;

	return false;
}

int CPlayer::GetScore()
{
	return m_totalScore;
}

void CPlayer::UpdateScore(int score)
{
	m_totalScore += score;
}

std::string CPlayer::GetName()
{
	return m_name;
}

bool CPlayer::GetIsLead()
{
	return m_bIsLead;
}

void CPlayer::SetIsLead(bool flag)
{
	m_bIsLead = flag;
}

void CPlayer::SortCardsInHand()
{
	std::sort(m_vecCardsInHand.begin(), m_vecCardsInHand.end());
}

int CPlayer::GetNumerOfCardsInHand()
{
	return m_vecCardsInHand.size();
}

void CPlayer::UpdateTotalScore(int scoreToAdd)
{
	m_totalScore += scoreToAdd;
}

void CPlayer::CollectCardInHand(CCard card)
{
	m_vecCardsInHand.emplace_back(card);
}

int CPlayer::TakeCardsAndUpdateScore(std::vector<CCard> cards)
{
	for (CCard c : cards)
		m_vecCardsTaken.emplace_back(c);

	int currentScore = CScoreCalculator::CalculateScore(cards);
	m_totalScore += currentScore;
	return currentScore;
}

std::vector<CCard> CPlayer::ReturnAllTakenCards()
{
	std::vector<CCard> vecReturnTaken{};
	if (!m_vecCardsTaken.empty())
	{
		std::copy(m_vecCardsTaken.begin(), m_vecCardsTaken.end(), std::back_inserter(vecReturnTaken));
		//vecReturnTaken = m_vecCardsTaken;
		m_vecCardsTaken.clear();
	}
	return vecReturnTaken;
}

std::string CPlayer::GetString()
{
	return this->GetName() + ": " + std::to_string(this->GetScore());
}

