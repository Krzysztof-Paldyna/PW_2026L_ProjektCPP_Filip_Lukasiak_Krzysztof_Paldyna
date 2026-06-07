#include "Card.h"

std::map<int, CardCreator> CardFactory::Registered_Cards;

Card::Card()
{
	Nazwa = "NienazwanaKarta";
	Energy = 1;
	Card_class = Attack_Card;
	CardType = None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	file_path = "None";
	update_texture();
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
	Nazwa = "Basic Attack";
	Energy = 1;
	Attack = 6;
	Card_class = Attack_Card;
	CardType = None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta Atakuje za 6 dmg";
	file_path = "resources/textures/AttackCardSprite.png";
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
	b->EndBattleCheck();
}
Card* AttackCard:: kreator()
{
	return new AttackCard();
}
AttackCard::~AttackCard()
{

}

//--------------------------------------------------------------ShieldCard-----------------------------------------------

ShieldCard::ShieldCard()
{
	Nazwa = "Basic Shield";
	Energy = 1;
	Shield = 5;
	Card_class = Skill_Card;
	CardType = None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta daje 5 Tarczy";
	file_path = "resources/textures/ShieldCardSprite.png";
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
	b->EndBattleCheck();
}
Card* ShieldCard::kreator()
{
	return new ShieldCard();
}
ShieldCard::~ShieldCard()
{

}
//--------------------------------------------------------------AttackShieldCard-----------------------------------------------
AttackShieldCard::AttackShieldCard()
{
	Nazwa = "Basic Attack\nShield";
	Energy = 1;
	Attack = 4;
	Shield = 2;
	Card_class = Attack_Card;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta Atakuje za 4 dmg\ni daje 2 tarczy";
	file_path = "resources/textures/AttackShieldCardSprite.png";
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
	b->EndBattleCheck();
}
Card* AttackShieldCard::kreator()
{
	return new AttackShieldCard();
}
AttackShieldCard::~AttackShieldCard()
{

}
//--------------------------------------------------------------DrawCard-----------------------------------------------
DrawCard::DrawCard()
{
	Nazwa = "Draw";
	Energy = 1;
	Card_class = Skill_Card;
	CardType = None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Dobierz dwie karty";
	file_path = "resources/textures/DrawCardSprite.png";
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
	b->EndBattleCheck();
}
Card* DrawCard::kreator()
{
	return new DrawCard();
}
DrawCard::~DrawCard()
{

}

//--------------------------------------------------------------FireAttack-----------------------------------------------
FireAttack::FireAttack()
{
	Nazwa = "Fire Attack";
	Energy = 1;
	Attack = 4;
	Card_class = Attack_Card;
	CardType = Fire;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Atakujesz ogniem 3 razy\npo 4 dmg i jesli masz tez\ntyp ogniowy atakujesz\n3 razy";
	file_path = "resources/textures/FireAttackSprite.png";
	update_texture();
}
Card* FireAttack::clone() 
{
	return new FireAttack(*this);
}
void FireAttack::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	if(CardType == b->Return_Player()->Return_Character().Return_Element_Type())
	{
		b->Return_Selected_Enemy()->TakeDamage(Attack);
	}
	b->EndBattleCheck();
}
Card* FireAttack:: kreator()
{
	return new FireAttack();
}
FireAttack::~FireAttack()
{

}
//--------------------------------------------------------------Splash-----------------------------------------------
Splash::Splash()
{
	Nazwa = "Splash";
	Energy = 0;
	Attack = 2;
	Card_class = Attack_Card;
	CardType = Water;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Lekko ochlapujesz wroga\nza 2 dmg, ale jesli\n jestes typu wodnego\ndobierasz tez karte";
	file_path = "resources/textures/SplashCardSprite.png";
	update_texture();
}
Card* Splash::clone() 
{
	return new Splash(*this);
}
void Splash::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	if(CardType == b->Return_Player()->Return_Character().Return_Element_Type())
	{
		b->Return_Player()->Draw_Card();
	}
	b->EndBattleCheck();
}
Card* Splash::kreator()
{
	return new Splash();
}
Splash::~Splash()
{

}
//--------------------------------------------------------------ThunderBolt-----------------------------------------------
ThunderBolt::ThunderBolt()
{
	Nazwa = "Thunder Bolt";
	Energy = 2;
	Attack = 13;
	Card_class = Attack_Card;
	CardType = Electric;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Walisz MEGA PIORUNEM\nza 13 dmg";
	file_path = "resources/textures/ThunderBoltSprite.png";
	update_texture();
}
Card* ThunderBolt::clone() 
{
	return new ThunderBolt(*this);
}
void ThunderBolt::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Selected_Enemy()->TakeDamage(Attack);
	b->EndBattleCheck();
}
Card* ThunderBolt::kreator()
{
	return new ThunderBolt();
}
ThunderBolt::~ThunderBolt()
{

}
//--------------------------------------------------------------CardFactory-----------------------------------------------
void CardFactory::regist(const int& id, CardCreator k)
{
	Registered_Cards[id] = k;
}
Card* CardFactory::create(const int& id)
{
	return Registered_Cards[id]();
}
void CardFactory::Initialize()
{
	if (!Registered_Cards.empty()) return;
	regist(1, &AttackCard::kreator);
    regist(2, &ShieldCard::kreator);
    regist(3, &AttackShieldCard::kreator);
    regist(4, &DrawCard::kreator);
	regist(5, &FireAttack::kreator);
	regist(6, &Splash::kreator);
	regist(7, &ThunderBolt::kreator);
}
Card* CardFactory::create_random()
{
	int g = 1 + rand() % Registered_Cards.size(); 
	return Registered_Cards[g]()->clone();
}