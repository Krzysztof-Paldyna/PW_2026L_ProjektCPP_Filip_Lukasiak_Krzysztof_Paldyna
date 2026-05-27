#ifndef CARD
#define CARD
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"
#include "graphics_object_card.hpp"
class Player;
class Enemy;
class Battle;

enum Card_Class
{
	Attack_Card = 1,
	Skill_Card
};
class Card : public graphics_object_card
{
protected:
	std::string Nazwa;
	std::string Opis;
	std::string Path;
	int Energy;
	Card_Class Card_class;
	ElementType CardType;

public:
	Card();
	Card(std::string n, int e);
	virtual Card* clone(); //Funkcja zeby mozna robic pare tych samych kart
	std::string Return_Card_Name();
	int Return_Card_Cost();
	int ChooseEnemy(const std::vector<Enemy>& en);
	virtual void Card_Effect(Battle* b);
	virtual ~Card();
};

typedef Card* (*CardCreator) (std::string n, int e);



class AttackCard: public Card
{
protected:
	int Attack = 1;
public:
	AttackCard();
	AttackCard(std::string n, int e, int a);
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~AttackCard();
	static Card* kreator(std::string n, int e);
	static int const Id = 1;
};


class ShieldCard: public Card
{
protected:
	int Shield = 1;
public:
	ShieldCard();
	ShieldCard(std::string n, int e);
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~ShieldCard();
	static Card* kreator(std::string n, int e);
	static int const Id = 2;
};

class AttackShieldCard : public Card
{
protected:
	int Attack = 1;
	int Shield = 1;
public:
	AttackShieldCard();
	AttackShieldCard(std::string n, int e, int a, int c);
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~AttackShieldCard();
	static Card* kreator(std::string n, int e);
	static int const Id = 3;
};

class CardFactory
{
private:
	static std::map<int, CardCreator> Registered_Cards;
public:
	static void regist(const int& id, CardCreator k);
	static Card* create(const int& id, std::string n, int e);
};
#endif
