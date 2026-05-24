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
#include <ctime>

class Player
{
protected:
	int Max_Energy;
	int Current_Energy;
	int Hand_Size = 3;
	Character Player_Char;
	std::vector<Card*> PlayerDeck;
	std::vector<Card*> HandCards;
	std::vector<Card*> DiscardDeck;
public:
	Player();
	~Player();

	void Set_Character(Character c);
	Character Return_Character();

	std::vector<Card*> Return_PlayerDeck();
	void All_Cards(); //wypisuje nazwy wszystkich kart
	void All_Discard_Cards(); // Wypisuje nazwy wszystkich kart w kupce Discarded/odrzyconych
	void All_Hand_Cards();
	Card* PlayCard();
	void Discard_Card_From_Hand(int g);
	void Discard_Card_From_Deck(int g);
	void Return_Discarded_Cards_to_Deck();

	void SetHand();
	void Give_Card_to_Hand(int g);
	void Give_Random_Card_to_Hand();

	int Return_Max_Energy();
	int Return_Current_Energy();
	void Reduce_Energy(int e);
	void Add_Energy(int e);
	void Reset_Energy();

	void Add_Card(Card* c);
	void Set_Hand_Size(int s);
};
#endif