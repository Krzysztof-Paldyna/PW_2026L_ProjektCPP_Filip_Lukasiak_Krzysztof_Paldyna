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

enum class Card_Class
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
	Card_Class Cardclass;
	Element_Type CardType;

public:
	Card();
	virtual Card* clone(); //Funkcja zeby mozna robic pare tych samych kart
	std::string Return_Card_Name();
	int Return_Card_Cost();
	int ChooseEnemy(const std::vector<Enemy>& en);
	virtual void Card_Effect(Battle* b);
	virtual ~Card();
	void Set_Color_By_Type();
};

typedef Card* (*CardCreator) ();



class AttackCard: public Card
{
protected:
	int Attack = 1;
public:
	AttackCard();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~AttackCard();
	static Card* kreator();
	static int const Id = 1;
};


class ShieldCard: public Card
{
protected:
	int Shield = 1;
public:
	ShieldCard();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~ShieldCard();
	static Card* kreator();
	static int const Id = 2;
};

class AttackShieldCard : public Card
{
protected:
	int Attack = 1;
	int Shield = 1;
public:
	AttackShieldCard();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~AttackShieldCard();
	static Card* kreator();
	static int const Id = 3;
};

class DrawCard: public Card
{
protected:
public:
	DrawCard();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~DrawCard();
	static Card* kreator();
	static int const Id = 4;
};

class FireAttack: public Card
{
protected:
	int Attack = 1;
public:
	FireAttack();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~FireAttack();
	static Card* kreator();
	static int const Id = 5;
};



class Splash: public Card
{
protected:
	int Attack = 1;
public:
	Splash();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~Splash();
	static Card* kreator();
	static int const Id = 6;
};

class ThunderBolt: public Card
{
protected:
	int Attack = 1;
public:
	ThunderBolt();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~ThunderBolt();
	static Card* kreator();
	static int const Id = 7;
};

class Flamethrower: public Card
{
protected:
	int Attack = 1;
public:
	Flamethrower();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~Flamethrower();
	static Card* kreator();
	static int const Id = 8;
};

class Earthquake: public Card
{
protected:
	int Attack = 1;
public:
	Earthquake();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~Earthquake();
	static Card* kreator();
	static int const Id = 9;
};

class Second_Wind: public Card
{
protected:
	int Shield = 1;
public:
	Second_Wind();
	virtual Card* clone();
	virtual void Card_Effect(Battle* b);
	virtual ~Second_Wind();
	static Card* kreator();
	static int const Id = 10;
};

class CardFactory
{
private:
	static std::map<int, CardCreator> Registered_Cards;
public:
	static void Initialize(); 
	static void regist(const int& id, CardCreator k);
	static Card* create(const int& id);
	static Card* create_random();
};
#endif
