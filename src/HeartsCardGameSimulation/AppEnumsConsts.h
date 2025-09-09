#pragma once

const int MAX_CARDS = 52;
const int MAX_CARDS_IN_SUIT = 13;
const int CARD_SUITS = 4;
const int TOTAL_PLAYERS = 4;
const int MAX_TRICKS = 13;
const int MAX_PASSES = 4;

enum class CARD_SUIT
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

enum class CARD_RANK
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

enum class PLAYER_TYPE
{
	HUMAN,
	COMPUTER
};

enum class PLAYER_POSITION
{
	NORTH = 1,
	EAST,
	SOUTH,
	WEST
};

enum class CARDS_PASSING_DIRECTION
{
	LEFT = 1,
	RIGHT,
	OPPOSITE,
	NONE
};