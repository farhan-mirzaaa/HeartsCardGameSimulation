#include "CGame.h"
#include "CConsoleLogger.h"
#include <thread>
#include <chrono>
#include <string>
#include "CCardsPassDirection.h"
#include "CScoreCalculator.h"
#include <algorithm>
#include "CCardsFactory.h"

using namespace std::chrono_literals;

CGame::CGame()
{
}

CGame::~CGame()
{
	CConsoleLogger::GetInstance()->PrintString("Game Ended! Thank you for your time.");
}

void CGame::Initialize()
{
	CConsoleLogger::GetInstance()->PrintString("Welcome to Hearts Card Game Simulation");
	CConsoleLogger::GetInstance()->PrintString("Game is Starting", false);
	for (int i : {1, 2, 3})
	{
		std::this_thread::sleep_for(1s);
		CConsoleLogger::GetInstance()->PrintString(".", i%3 == 0 ? true : false);
	}
	m_playerManager.CreatePlayers(TOTAL_PLAYERS, 0);
	m_cardsManager.CreateCards();
}

void CGame::Run()
{
	while (!m_isGameEnded)
	{
		CreateNewRound();

		ExecuteRound();

		auto looser = m_playerManager.IsAnyPlayerLost();
		if (looser.second >= CScoreCalculator::GetMaxLooserScore())
			m_isGameEnded = true;
	}

	CConsoleLogger::GetInstance()->PrintString("Game Ended!");
	CConsoleLogger::GetInstance()->PrintString("Results:");
	//sort the players in ascending order on the basis of score
	std::sort(m_playerManager.GetPlayers().begin(), m_playerManager.GetPlayers().end(),
		[](std::shared_ptr<CPlayer>& a, std::shared_ptr<CPlayer>& b) {
			return a->GetScore() < b->GetScore();
		});
	//print final scores
	for (auto p : m_playerManager.GetPlayers())
	{
		CConsoleLogger::GetInstance()->PrintString(p->GetString());
	}
}

void CGame::CreateNewRound()
{
	if (m_vecRounds.size() > 0)
	{
		//retrieve all cards from players
		m_cardsManager.RetreiveCards(m_playerManager.GetPlayers());
	}

	CRound round{};
	CConsoleLogger::GetInstance()->PrintString(
		"Round: " + std::to_string(round.GetRoundNumber()) + " - Started...");
	
	m_cardsManager.ShuffleCards(3);
	m_cardsManager.DistributeCards(m_playerManager.GetPlayers());
	CConsoleLogger::GetInstance()->PrintString("Cards distributed among players.");

	round.PassCards(m_playerManager.GetPlayers());
	CConsoleLogger::GetInstance()->PrintString(
		"Cards passed in direction: " + CCardsPassDirection::to_string(round.GetPassDirection()));

	m_vecRounds.push_back(round);
}

void CGame::ExecuteRound()
{
	m_vecRounds[m_vecRounds.size() - 1].ExecuteRound(m_playerManager);

	m_vecRounds[m_vecRounds.size() - 1].EndRound(m_playerManager);

	CConsoleLogger::GetInstance()->PrintString(m_vecRounds[m_vecRounds.size() - 1].GetString());
}
