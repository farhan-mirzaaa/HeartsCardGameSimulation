#pragma once
#include "CPlayer.h"
#include <string>

class CHumanPlayer :
    public CPlayer
{
public:
    CHumanPlayer();
    CHumanPlayer(std::string name, PLAYER_POSITION position);

    virtual std::vector<CCard> GetPassCards() override;
    virtual CCard ChooseCard(bool isFirstTrick, std::vector<CCard> trickCards) override;
};

