#include "CHumanPlayer.h"

CHumanPlayer::CHumanPlayer()
{
}

CHumanPlayer::CHumanPlayer(std::string name, PLAYER_POSITION position)
	:CPlayer(name, position)
{
	m_playerType = PLAYER_TYPE::HUMAN;
}

std::vector<CCard> CHumanPlayer::GetPassCards()
{
	return std::vector<CCard>();
}

CCard CHumanPlayer::ChooseCard(bool isFirstTrick, std::vector<CCard> trickCards)
{
	return CCard();
}
