#include "Card.h"

std::map<int, CardCreator> CardFactory::Registered_Cards;

Card::Card(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Card_class = Attack_Card;
	CardType = None;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	file_path = "None";
}
Card::Card()
{
	Nazwa = "NienazwanaKarta";
	Energy = 1;
	Card_class = Attack_Card;
	CardType = None;
}
Card* Card::clone()
{
	return new Card(*this);
}
void Card::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	std::cout << "Efect Karty ktora nie ma efektu czyli jest cos zle "<< std::endl;
}
int Card::ChooseEnemy(const std::vector<Enemy>& en)
{
	int g;
	if (en.size() == 1)
	{
		return 0;
	}
	else
	{
		std::cout << "Wybierz wroga " << std::endl;
		std::cin >> g;
		return g;
	}
	return 0;
}
std::string Card::Return_Card_Name()
{
	return Nazwa;
}
int Card::Return_Card_Cost()
{
	return Energy;
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
	CardType = None;
}
AttackCard::AttackCard(std::string n, int e, int a)
{
	Nazwa = n;
	Energy = e;
	Attack = a;
	Card_class = Attack_Card;
	CardType = None;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Ta Karta Atakuje za 5 dmg";
	file_path = "None";
}
Card* AttackCard::clone() 
{
	return new AttackCard(*this);
}
void AttackCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	int w = ChooseEnemy(b->Return_Enemies());
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " <<b->Return_Enemies().at(w).Return_Name() << std::endl;
	b->Return_Enemies().at(w).TakeDamage(Attack);
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
	CardType = None;
}
ShieldCard::ShieldCard(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Shield = 5;
	Card_class = Skill_Card;
	CardType = None;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Ta Karta daje 5 Tarczy";
	file_path = "None";
}
Card* ShieldCard::clone() 
{
	return new ShieldCard(*this);
}
void ShieldCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	std::cout << "Efect Karty Obrony!!! "<<b->Return_Player()->Return_Character().Return_Name() << " Dostaje " << Shield << " Tarczy " << std::endl;
	b->Return_Player()->Return_Character().Add_Shield(Shield);
}
Card* ShieldCard::kreator(std::string n, int e)
{
	return new ShieldCard(n, e);
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
	CardType = None;
}
AttackShieldCard::AttackShieldCard(std::string n, int e, int a, int c)
{
	Nazwa = n;
	Energy = e;
	Attack = a;
	Shield = c;
	Card_class = Attack_Card;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Ta Karta Atakuje za 2 dmg\ni daje 2 tarczy";
	file_path = "resources/textures/aaa.jpg";
}
Card* AttackShieldCard::clone()
{
	return new AttackShieldCard(*this);
}
void AttackShieldCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	int w = ChooseEnemy(b->Return_Enemies());
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " << b->Return_Enemies().at(w).Return_Name() << " i " << b->Return_Player()->Return_Character().Return_Name() << " Dostaje " << Shield << " Tarczy " << std::endl;
	b->Return_Enemies().at(w).TakeDamage(Attack);
	b->Return_Player()->Return_Character().Add_Shield(Shield);
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
