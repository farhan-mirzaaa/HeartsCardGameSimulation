#include "CScores.h"

CScores::CScores(int score, std::string playerName): 
	m_score(score), m_playerName(playerName)
{
}

std::string CScores::GetString()
{
	return (m_playerName + ": " + std::to_string(m_score));
}
