#include "CComputerPlayer.h"
#include <algorithm>

CComputerPlayer::CComputerPlayer()
{
}

CComputerPlayer::CComputerPlayer(PLAYER_POSITION position)
	: CPlayer(position)
{
	m_playerType = PLAYER_TYPE::COMPUTER;
}

std::vector<CCard> CComputerPlayer::GetPassCards()
{
	SortCardsInHand();

	std::vector<CCard> passCards{};

	for (int i = 0; i < 3; i++) {	//to choose three cards
		CCard dangCard;
		if (m_vecCardsInHand.size() > 0)
		{
			auto tempItr = m_vecCardsInHand.begin();
			dangCard = *tempItr;
			bool noHearts = true;
			for (auto it = m_vecCardsInHand.begin(); it != m_vecCardsInHand.end(); ++it)
			{
				//if card is from hearts or queen of spades then select these with higher in number
				if (it->GetSuit().Suit() == CARD_SUIT::SPADES &&
					it->GetRank().Rank() == CARD_RANK::QUEEN)
				{
					dangCard = (*it);
					tempItr = it;
					break;
				}
				else if (it->GetSuit().Suit() == CARD_SUIT::HEARTS)
				{
					if ((it->GetRank().Rank() > dangCard.GetRank().Rank())
						&& dangCard.GetSuit().Suit() == CARD_SUIT::HEARTS)
					{
						dangCard = (*it);
						tempItr = it;
					}
					else
					{
						dangCard = (*it);
						tempItr = it;
					}
					noHearts = false;
				}
				if (noHearts == true)
				{
					if (it->GetRank().Rank() > dangCard.GetRank().Rank())
					{
						dangCard = (*it);
						tempItr = it;
					}
				}
			}

			passCards.emplace_back(dangCard);
			m_vecCardsInHand.erase(tempItr);
		}
	}

	return passCards;
}

CCard CComputerPlayer::ChooseCard(bool isFirstTrick, std::vector<CCard> trickCards)
{
	CCard cardToReturn;
	if (m_vecCardsInHand.size() == 1)
	{
		cardToReturn = m_vecCardsInHand[0];
		m_vecCardsInHand.clear();
		return cardToReturn;
	}
	//sort the cards in ascending order based on their rank only
	std::sort(m_vecCardsInHand.begin(), m_vecCardsInHand.end(),
		[](CCard& a, CCard& b) {
			return a.GetRank().Rank() < b.GetRank().Rank();
		});

	if (m_bIsLead == true && trickCards.empty())
	{
		for (auto it = m_vecCardsInHand.begin(); it != m_vecCardsInHand.end(); ++it)
		{
			if (isFirstTrick == true)
			{
				if (it->GetRank().Rank() == CARD_RANK::TWO &&
					it->GetSuit().Suit() == CARD_SUIT::CLUBS)
				{
					cardToReturn = (*it);
					m_vecCardsInHand.erase(it);
					break;
				}
			}
			else
			{
				//take least card for this trick
				cardToReturn = m_vecCardsInHand.front();
				m_vecCardsInHand.erase(m_vecCardsInHand.begin());
				break;
			}
		}
	}
	else
	{
		//check the trick start suit and select card
		CARD_SUIT startSuit = trickCards[0].GetSuit().Suit();

		bool foundOfSameSuit{ false };

		//sort the trick cards in ascending order based on their rank only
		std::sort(trickCards.begin(), trickCards.end(),
			[](CCard& a, CCard& b) {
				return a.GetRank().Rank() < b.GetRank().Rank();
			});

		auto selItr = m_vecCardsInHand.begin();
		for (auto it = m_vecCardsInHand.begin(); it != m_vecCardsInHand.end(); ++it)
		{
			if (startSuit == it->GetSuit().Suit())
			{
				if (foundOfSameSuit == false)
					selItr = it;
				foundOfSameSuit = true;
				
				//find lowest possible
				if (it != selItr
					&& (it->GetRank().Rank() < trickCards[trickCards.size() - 1].GetRank().Rank()))
				{
					selItr = it;
					break;
				}
			}
		}
		if (foundOfSameSuit == false)
		{
			//choose queen of spades, hearts or any other high rank card
			bool found{ false };
			CCard highest;
			auto itrToDel = m_vecCardsInHand.end();
			for (auto it = m_vecCardsInHand.begin(); it != m_vecCardsInHand.end(); ++it)
			{
				if (it->GetRank().Rank() == CARD_RANK::QUEEN &&
					it->GetSuit().Suit() == CARD_SUIT::SPADES)
				{
					highest = *it;
					found = true;
					itrToDel = it;
					break;
				}
				else if ((it->GetRank().Rank() > highest.GetRank().Rank())
					&& (it->GetSuit().Suit() == CARD_SUIT::HEARTS) )
				{
					highest = *it;
					found = true;
					itrToDel = it;
				}
			}
			if (found == false)
			{
				cardToReturn = m_vecCardsInHand.back();
				m_vecCardsInHand.pop_back();
			}
			else
			{
				cardToReturn = highest;
				m_vecCardsInHand.erase(itrToDel);
			}
		}
		else
		{
			cardToReturn = *selItr;
			m_vecCardsInHand.erase(selItr);
		}
	}
	return cardToReturn;
}
