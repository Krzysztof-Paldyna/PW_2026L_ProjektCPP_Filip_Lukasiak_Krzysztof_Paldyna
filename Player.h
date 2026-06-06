#ifndef PLAYER
#define PLAYER
#include "Enemy.h"
#include "Card.h"
class Card;
class Character;
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
	int Hand_Size;
	PlayerCharacter Player_Char;
	std::vector<Card*> PlayerDeck;
	std::vector<Card*> HandCards;
	std::vector<Card*> DiscardDeck;
public:
	Player();
	~Player();

	void Set_Character(PlayerCharacter c);
	PlayerCharacter& Return_Character();

	std::vector<Card*> &Return_PlayerDeck();
	std::vector<Card*> &Return_PlayerHand();
	std::vector<Card*> &Return_DiscardDeck();
	void All_Cards(); //wypisuje nazwy wszystkich kart
	void All_Discard_Cards(); // Wypisuje nazwy wszystkich kart w kupce Discarded/odrzyconych
	void All_Hand_Cards();
	Card* PlayCard(int g);
	void Discard_Card_From_Hand(int g);
	void Discard_Card_From_Deck(int g);
	void Return_Discarded_Cards_to_Deck();	//zwraca wszystkie karty z talii odrzuconych do talii dobieranych i je przetasowuje
	void Return_Hand_Cards_to_Deck();
	void RerollHand();

	void SetHand();
	void Give_Card_to_Hand(int g);
	void Draw_Card();

	int Return_Max_Energy();
	int Return_Current_Energy();
	void Reduce_Energy(int e);
	void Add_Energy(int e);
	void Reset_Energy();


	void Add_Card(Card* c);
	void Set_Hand_Size(int s);
};
#endif