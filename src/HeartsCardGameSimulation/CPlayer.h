#pragma once
#include <string>
#include "AppEnumsConsts.h"
#include "CCard.h"
#include <vector>
#include <memory>

class CPlayer
{
	
protected:
	std::string		m_name{};
	int				m_totalScore{};
	PLAYER_POSITION	m_postion{};
	PLAYER_TYPE		m_playerType{PLAYER_TYPE::COMPUTER};
	bool			m_bIsLead{false};

	std::vector<CCard> m_vecCardsInHand{};

	std::vector<CCard> m_vecCardsTaken{};

public:
	CPlayer();
	CPlayer(PLAYER_POSITION position);
	CPlayer(std::string name, PLAYER_POSITION position);
	virtual ~CPlayer() = default;

	bool IsOnwerOfTwoOfClubs();
	bool HaveAllHeartsAndQueenOfSpades();
	int GetScore();
	void UpdateScore(int score);
	std::string GetName();
	bool GetIsLead();
	void SetIsLead(bool flag);
	void SortCardsInHand();
	int GetNumerOfCardsInHand();

	void UpdateTotalScore(int scoreToAdd);
	void CollectCardInHand(CCard card);
	int TakeCardsAndUpdateScore(std::vector<CCard> cards);
	std::vector<CCard> ReturnAllTakenCards();

	virtual std::string GetString();

	virtual std::vector<CCard> GetPassCards() = 0;
	virtual CCard ChooseCard(bool isFirstTrick, std::vector<CCard> trickCards) = 0;
};

