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
	update_texture();
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
AttackCard::AttackCard(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Attack = 6;
	Card_class = Attack_Card;
	CardType = None;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Ta Karta Atakuje za 6 dmg";
	file_path = "resources/textures/BasicAttack.png";
	update_texture();
}
Card* AttackCard::clone() 
{
	return new AttackCard(*this);
}
void AttackCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " <<b->Return_Selected_Enemy()->Return_Name() << std::endl;
	std::cout<< "Ma aktualnie "<< b->Return_Selected_Enemy()->Return_CurrentHP()<<std::endl;
}
Card* AttackCard:: kreator(std::string n, int e)
{
	return new AttackCard(n, e);
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
	update_texture();
}
Card* ShieldCard::clone() 
{
	return new ShieldCard(*this);
}
void ShieldCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Player()->Return_Character().Add_Shield(Shield);
	std::cout << "Efect Karty Tarczy!!! Dodaje " << Shield << " Punktów tarczy " << std::endl;
	std::cout<< "Ma aktualnie "<< b->Return_Player()->Return_Character().Return_Shield() <<std::endl;
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
AttackShieldCard::AttackShieldCard(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Attack = 4;
	Shield = 2;
	Card_class = Attack_Card;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Ta Karta Atakuje za 4 dmg\ni daje 2 tarczy";
	file_path = "resources/textures/aaa.jpg";
	update_texture();
}
Card* AttackShieldCard::clone()
{
	return new AttackShieldCard(*this);
}
void AttackShieldCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	b->Return_Player()->Return_Character().Add_Shield(Shield);
	std::cout << "Efect Karty Ataku!!! Zadaje " << Attack << " Obrazen " <<b->Return_Selected_Enemy()->Return_Name() << std::endl;
	std::cout<< "Ma aktualnie "<< b->Return_Selected_Enemy()->Return_CurrentHP()<<std::endl;
}
Card* AttackShieldCard::kreator(std::string n, int e)
{
	return new AttackShieldCard(n, e);
}
AttackShieldCard::~AttackShieldCard()
{

}
//--------------------------------------------------------------DrawCard-----------------------------------------------
DrawCard::DrawCard()
{
	Nazwa = "NienazwanaKartaTarczy";
	Energy = 1;
	Card_class = Skill_Card;
	CardType = None;
}
DrawCard::DrawCard(std::string n, int e)
{
	Nazwa = n;
	Energy = e;
	Card_class = Skill_Card;
	CardType = None;
	//elementy graficzne:
	name = n;
	cost = std::to_string(e);
	text = "Dobierz dwie karty";
	file_path = "None";
	update_texture();
}
Card* DrawCard::clone() 
{
	return new DrawCard(*this);
}
void DrawCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	for(int i = 0; i < 2; ++i){
		b->Return_Player()->Draw_Card();
	}
}
Card* DrawCard::kreator(std::string n, int e)
{
	return new DrawCard(n, e);
}
DrawCard::~DrawCard()
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
void CardFactory::Initialize()
{
	if (!Registered_Cards.empty()) return;
	regist(1, &AttackCard::kreator);
    regist(2, &ShieldCard::kreator);
    regist(3, &AttackShieldCard::kreator);
    regist(4, &DrawCard::kreator);
}