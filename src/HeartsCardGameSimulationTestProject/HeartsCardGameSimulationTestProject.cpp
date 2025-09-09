#include "pch.h"
#include "CppUnitTest.h"
#include "CScoreCalculator.h"
#include "CCardsFactory.h"
#include "CGame.h"
#include "CRound.h"
#include "CCardsManager.h"
#include "CPlayerManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HeartsCardGameSimulationTestProject
{
    //Unit tests
	TEST_CLASS(UnitTests)
	{
    public:
        TEST_METHOD(CalculateScoreTest)
        {
            std::vector<CCard> cards = {
                CCardsFactory::CreateCardObject(CARD_SUIT::HEARTS, CARD_RANK::TWO),
                CCardsFactory::CreateCardObject(CARD_SUIT::SPADES, CARD_RANK::QUEEN),
                CCardsFactory::CreateCardObject(CARD_SUIT::CLUBS, CARD_RANK::ACE)
            };
            Assert::AreEqual(14, CScoreCalculator::CalculateScore(cards));  // 1 + 13 + 0
        }

        TEST_METHOD(MaxScoreTest)
        {
            Assert::AreEqual(26, CScoreCalculator::CalculateScore(true));
        }

        TEST_METHOD(MaxLooserTest)
        {
            Assert::AreEqual(100, CScoreCalculator::GetMaxLooserScore());
        }
	};

    // Integration Tests
    TEST_CLASS(IntegrationTests)
    {
    public:
        TEST_METHOD(RoundPassCardsTest)
        {
            CPlayerManager pManager;
            pManager.CreatePlayers(TOTAL_PLAYERS, 0);
            Assert::AreEqual(TOTAL_PLAYERS, pManager.GetNumberOfPlayers());

            CCardsManager cardsManager;
            cardsManager.CreateCards();
            cardsManager.ShuffleCards(3);
            cardsManager.DistributeCards(pManager.GetPlayers());

            CRound round;
            round.PassCards(pManager.GetPlayers());

            for (auto& p : pManager.GetPlayers()) {
                Assert::AreEqual(13, p->GetNumerOfCardsInHand());
            }
        }

        TEST_METHOD(RoundExecuteTrickTest)
        {
            CPlayerManager pManager;
            pManager.CreatePlayers(TOTAL_PLAYERS, 0);
            auto& players = pManager.GetPlayers();

            players[0]->CollectCardInHand(CCardsFactory::CreateCardObject(CARD_SUIT::CLUBS, CARD_RANK::TEN));
            players[1]->CollectCardInHand(CCardsFactory::CreateCardObject(CARD_SUIT::CLUBS, CARD_RANK::JACK));
            players[2]->CollectCardInHand(CCardsFactory::CreateCardObject(CARD_SUIT::CLUBS, CARD_RANK::QUEEN));
            players[3]->CollectCardInHand(CCardsFactory::CreateCardObject(CARD_SUIT::CLUBS, CARD_RANK::ACE));

            pManager.SetLead(players[2]->GetName());  // SOUTH_PLAYER leads with QUEEN

            CRound round;
            std::string looser = round.ExecuteTrick(pManager);

            Assert::AreEqual(players[3]->GetName().c_str(), looser.c_str());  // WEST_PLAYER has ACE
            Assert::AreEqual(0, players[3]->GetScore());  // No penalties in this trick
            Assert::AreEqual(0, players[3]->GetNumerOfCardsInHand()); //no cards in hand at the end of the trick
        }

        TEST_METHOD(ExecuteRoundTest)
        {
            CPlayerManager pManager;
            pManager.CreatePlayers(TOTAL_PLAYERS, 0);

            CCardsManager cardsManager;
            cardsManager.CreateCards();
            cardsManager.ShuffleCards(2);
            cardsManager.DistributeCards(pManager.GetPlayers());

            // Find and set lead for Two of Clubs
            for (auto& p : pManager.GetPlayers()) {
                if (p->IsOnwerOfTwoOfClubs()) {
                    pManager.SetLead(p->GetName());
                    break;
                }
            }

            CRound round;
            round.ExecuteRound(pManager);
            round.EndRound(pManager);

            int totalScore = 0;
            for (auto& p : pManager.GetPlayers()) {
                totalScore += p->GetScore();
            }
            Assert::AreEqual(26, totalScore);  // All penalties distributed (13 Hearts + 13 Queen of Spades)
            Assert::IsTrue(round.IsRoundCompleted());
        }
    };
}
