#include "Card.h"

std::map<int, CardCreator> CardFactory::Registered_Cards;

Card::Card(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Card_class = Attack_Card;
}
Card::Card()
{
	Nazwa = "NienazwanaKarta";
	Energy = 1;
	Card_class = Attack_Card;
}
void Card::Card_Effect()
{
	std::cout << "Efect Karty ktora nie ma efektu czyli jest cos zle "<< std::endl;
}
Card::~Card()
{

}
//--------------------------------------------------------------AttackCard-----------------------------------------------
AttackCard::AttackCard()
{
	Nazwa = "NienazwanaKartaAtaku";
	Energy = 1;
	Card_class = Attack_Card;
	Attack = 1;
}
AttackCard::AttackCard(std::string n, int e, int a)
{
	Nazwa = n;
	Energy = e;
	Attack = a;
	Card_class = Attack_Card;
}
void AttackCard::Card_Effect()
{
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " << std::endl;
}
Card* AttackCard:: kreator(std::string n, int e)
{
	return new AttackCard(n, e, 3);
}
AttackCard::~AttackCard()
{

}

//--------------------------------------------------------------ShieldCard-----------------------------------------------
ShieldCard::ShieldCard()
{
	Nazwa = "NienazwanaKartaTarczy";
	Energy = 1;
	Card_class = Skill_Card;
	Shield = 1;
}
ShieldCard::ShieldCard(std::string n, int e, int s)
{
	Nazwa = n;
	Energy = e;
	Shield = s;
	Card_class = Skill_Card;
}
void ShieldCard::Card_Effect()
{
	std::cout << "Efect Karty Obrony!!! Dostaje " << Shield << " Tarczy " << std::endl;
}
Card* ShieldCard::kreator(std::string n, int e)
{
	return new ShieldCard(n, e, 5);
}
ShieldCard::~ShieldCard()
{

}
//--------------------------------------------------------------CardFactory-----------------------------------------------
void CardFactory::regist(const int& id, CardCreator k)
{
	Registered_Cards[id] = k;
}
Card* CardFactory::create(const int& id, std::string n, int e)
{
	return Registered_Cards[id](n, e);
}