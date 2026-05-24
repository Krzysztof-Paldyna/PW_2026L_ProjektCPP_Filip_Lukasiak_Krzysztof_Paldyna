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
Card* Card::clone()
{
	return new Card(*this);
}
void Card::Card_Effect()
{
	std::cout << "Efect Karty ktora nie ma efektu czyli jest cos zle "<< std::endl;
}
std::string Card::Return_Card_Name()
{
	return Nazwa;
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
Card* AttackCard::clone() 
{
	return new AttackCard(*this);
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
Card* ShieldCard::clone() 
{
	return new ShieldCard(*this);
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
//--------------------------------------------------------------AttackShieldCard-----------------------------------------------
AttackShieldCard::AttackShieldCard()
{
	Nazwa = "NienazwanaKartaAtaku";
	Energy = 1;
	Card_class = Attack_Card;
	Attack = 1;
}
AttackShieldCard::AttackShieldCard(std::string n, int e, int a, int c)
{
	Nazwa = n;
	Energy = e;
	Attack = a;
	Shield = c;
	Card_class = Attack_Card;
}
Card* AttackShieldCard::clone()
{
	return new AttackShieldCard(*this);
}
void AttackShieldCard::Card_Effect()
{
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " <<" i  Dostaje " << Shield << " Tarczy " << std::endl;
}
Card* AttackShieldCard::kreator(std::string n, int e)
{
	return new AttackShieldCard(n, e, 2, 2);
}
AttackShieldCard::~AttackShieldCard()
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