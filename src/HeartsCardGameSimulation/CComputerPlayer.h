#pragma once
#include "CPlayer.h"

class CComputerPlayer :
    public CPlayer
{
public:
    CComputerPlayer();
    CComputerPlayer(PLAYER_POSITION position);

    virtual std::vector<CCard> GetPassCards() override;
    virtual CCard ChooseCard(bool isFirstTrick, std::vector<CCard> trickCards) override;
};

