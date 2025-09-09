#include "CRound.h"
#include "CCard.h"
#include "CScoreCalculator.h"

int CRound::g_nextNumber = 1;

CRound::CRound()
{
	m_number = g_nextNumber++;
}

int CRound::GetRoundNumber()
{
    return m_number;
}

bool CRound::IsRoundCompleted()
{
    return m_bIsCompleted;
}

CARDS_PASSING_DIRECTION CRound::GetPassDirection()
{
    return m_cardsPassingDirection;
}

void CRound::RecordScores(const std::vector<std::shared_ptr<CPlayer>>& vecPlayers)
{
	for (auto& p : vecPlayers)
	{
		m_vecPlayerScores.emplace_back(CScores((*p).GetScore(), (*p).GetName()));
	}
}

void CRound::PassCards(std::vector<std::shared_ptr<CPlayer>>& players)
{
    m_cardsPassingDirection = (CARDS_PASSING_DIRECTION)(m_number % 4);

    if (m_cardsPassingDirection == CARDS_PASSING_DIRECTION::NONE)
        return; //skip this round

    std::vector<std::vector<CCard>> totalPasses{};
    totalPasses.resize(MAX_PASSES);
    for (int i = 0; i < MAX_PASSES; ++i)
        totalPasses[i] = players[i]->GetPassCards();

    auto passTo = [&](int i) {
        if (m_cardsPassingDirection == CARDS_PASSING_DIRECTION::LEFT)
            return (i + 1) % 4;
        if (m_cardsPassingDirection == CARDS_PASSING_DIRECTION::RIGHT)
            return (i + 3) % 4;
        return (i + 2) % 4;
    };

    for (int i = 0; i < MAX_PASSES; ++i)
    {
        int pIndex = passTo(i);

        for (auto& c : totalPasses[i]) //pass cards to player
            players[pIndex]->CollectCardInHand(c);

        players[pIndex]->SortCardsInHand();
    }
}

void CRound::ExecuteRound(CPlayerManager& pManager)
{
    std::vector<std::shared_ptr<CPlayer>>& players = pManager.GetPlayers();
    //find trick lead
    for (auto& p : players)
    {
        if (p->IsOnwerOfTwoOfClubs() == true)
        {
            pManager.SetLead(p->GetName());
            break;
        }
    }

    for (int i = 0; i < MAX_TRICKS; i++)
    {
        std::string trickLooser = this->ExecuteTrick(pManager);

        pManager.SetLead(trickLooser);  //set lead for next trick

        /*for (auto& p : pManager.GetPlayers())
        {
            int score = p->GetScore();
            score++;
        }*/
    }
}

std::string CRound::ExecuteTrick(CPlayerManager& pManager)
{
    std::vector<std::shared_ptr<CPlayer>>& players = pManager.GetPlayers();
    m_currentTrickNumber++;

    //find initial player to start with

    std::vector<CCard> trickCards{};
    std::vector<std::string> playerNames{};

    auto leadItr = std::find_if(players.begin(), players.end(),
        [](std::shared_ptr<CPlayer>& p) {
            return p->GetIsLead() == true;
        });

    bool leadFound{ false };
    if (leadItr != players.end())
    {
        trickCards.emplace_back((*leadItr)->ChooseCard(
            m_currentTrickNumber == 1 ? true : false, trickCards));
        playerNames.emplace_back((*leadItr)->GetName());
        leadFound = true;
    }

    for (auto& p : players)
    {
        if (leadFound == true && p->GetIsLead() == true)
            continue;

        playerNames.emplace_back(p->GetName());
        trickCards.emplace_back(p->ChooseCard(
            m_currentTrickNumber == 1 ? true : false, trickCards));
    }

    //now find looser of the trick and return its name, send cards to looser
    CARD_SUIT trickSuit = trickCards[0].GetSuit().Suit();
    int looserIndex{}; int highestRank{};
    for (int i=0; i<trickCards.size(); i++)
    {
        if (trickSuit == trickCards[i].GetSuit().Suit())
        {
            if (highestRank < (int)trickCards[i].GetRank().Rank())
            {
                highestRank = (int)trickCards[i].GetRank().Rank();
                looserIndex = i;
            }
        }
    }

    pManager.HandoverTrickCardsToLooser(playerNames[looserIndex], trickCards);

    return playerNames[looserIndex];
}

void CRound::EndRound(CPlayerManager& pManager)
{
    std::vector<std::shared_ptr<CPlayer>>& players = pManager.GetPlayers();
    //Update Scores on round end
    std::string strPName = pManager.GetIsAnyPlayerHaveAllHeartsAndQueenOfSpades();
    int haveAllScore{};
    if (strPName != "")
        haveAllScore = CScoreCalculator::CalculateScore(true);
    for (auto& p : players)
    {
        if (strPName != "")
        {
            if (p->GetName() == strPName)
                p->UpdateScore(-haveAllScore);
            else
                p->UpdateScore(haveAllScore);
        }
        int score = p->GetScore();
        m_vecPlayerScores.emplace_back(CScores(p->GetScore(), p->GetName()));
    }

    m_bIsCompleted = true;
}

std::string CRound::GetString()
{
    std::string str = "Round: " + std::to_string(m_number) + "\nScores: ";
    for (auto s : m_vecPlayerScores)
    {
        str += s.GetString() + "  ";
    }
    return str;
}
