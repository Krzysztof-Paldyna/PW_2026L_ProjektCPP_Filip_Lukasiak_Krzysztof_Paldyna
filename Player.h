#ifndef PLAYER
#define PLAYER
#include "Character.h"
#include "Card.h"
class Character;
class Card;
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>


class Player
{
protected:
	Character Player_Char;
	std::vector<Card> PlayerDeck;
public:
	Player();
	~Player();
	void Set_Character(Character c);
	void Add_Card(Card c);
};
#endif