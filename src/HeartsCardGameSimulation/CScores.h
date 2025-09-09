#pragma once
#include <string>

class CScores
{
private:
	std::string m_playerName{};
	int m_score;

public:
	CScores(int score, std::string playerName);
	std::string GetString();
};

