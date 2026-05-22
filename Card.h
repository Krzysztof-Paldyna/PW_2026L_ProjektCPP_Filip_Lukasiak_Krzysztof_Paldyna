#ifndef CARD
#define CARD
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

enum Card_Class
{
	Attack_Card = 1,
	Skill_Card
};
class Card
{
protected:
	std::string Nazwa;
	int Energy;
	Card_Class Card_class;
public:
	Card();
	Card(std::string n, int e);
	virtual void Card_Effect();
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
	virtual void Card_Effect();
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
	ShieldCard(std::string n, int e, int s);
	virtual void Card_Effect();
	virtual ~ShieldCard();
	static Card* kreator(std::string n, int e);
	static int const Id = 2;
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
