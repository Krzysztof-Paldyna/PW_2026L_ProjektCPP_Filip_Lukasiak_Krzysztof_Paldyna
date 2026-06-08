#include "Card.h"

std::map<int, CardCreator> CardFactory::Registered_Cards;

Card::Card()
{
	Nazwa = "NienazwanaKarta";
	Energy = 1;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	file_path = "None";
	Set_Color_By_Type();
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

void Card::Set_Color_By_Type()
{	
	switch(CardType){
	case Element_Type::Fire:
		set_color(255, 64, 20);
		break;
	case Element_Type::Water:
		set_color(0, 160, 255);
		break;
	case Element_Type::Air:
		set_color(230, 255, 255);
		break;
	case Element_Type::Ground:
		set_color(140, 64, 12);
		break;
	case Element_Type::Plant:
		set_color(0, 200, 0);
		break;
	case Element_Type::Electric:
		set_color(255, 255, 64);
		break;
	case Element_Type::Metal:
		set_color(200, 200, 200);
	default:
		set_color(128, 128, 128);
		break;
	}
}

//--------------------------------------------------------------AttackCard-----------------------------------------------
AttackCard::AttackCard()
{
	Nazwa = "Basic Attack";
	Energy = 1;
	Attack = 6;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta Atakuje za 6 dmg";
	file_path = "resources/textures/AttackCardSprite.png";
	Set_Color_By_Type();
	update_texture();
}
Card* AttackCard::clone() 
{
	return new AttackCard(*this);
}
void AttackCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);
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
	Cardclass = Card_Class::Skill_Card;
	CardType = Element_Type::None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta daje 5 Tarczy";
	file_path = "resources/textures/ShieldCardSprite.png";
	Set_Color_By_Type();
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
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Ta Karta Atakuje za 4 dmg\ni daje 2 tarczy";
	file_path = "resources/textures/AttackShieldCardSprite.png";
	Set_Color_By_Type();
	update_texture();
}
Card* AttackShieldCard::clone()
{
	return new AttackShieldCard(*this);
}
void AttackShieldCard::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);
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
	Cardclass = Card_Class::Skill_Card;
	CardType = Element_Type::None;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Dobierz dwie karty";
	file_path = "resources/textures/DrawCardSprite.png";
	Set_Color_By_Type();
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
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Fire;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Atakujesz ogniem 2 razy\npo 4 dmg. Jezeli jestes\ntypu ogniowego atakujesz\ndodatkowy raz";
	file_path = "resources/textures/FireAttackSprite.png";
	Set_Color_By_Type();
	update_texture();
}
Card* FireAttack::clone() 
{
	return new FireAttack(*this);
}
void FireAttack::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	int attack_times = 2;
	if(CardType == b->Return_Player()->Return_Character().Return_Element_Type())
	{
		++attack_times;
	}
	for(int i = 0; i < attack_times; ++i)
	{
		b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);
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
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Water;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Lekko ochlapujesz wroga\nza 2 dmg, ale jesli\n jestes typu wodnego\ndobierasz tez karte";
	file_path = "resources/textures/SplashCardSprite.png";
	Set_Color_By_Type();
	update_texture();
}
Card* Splash::clone() 
{
	return new Splash(*this);
}
void Splash::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);
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
	Attack = 15;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Electric;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Walisz MEGA PIORUNEM\nza 15 dmg";
	file_path = "resources/textures/ThunderBoltSprite.png";
	Set_Color_By_Type();
	update_texture();
}
Card* ThunderBolt::clone() 
{
	return new ThunderBolt(*this);
}
void ThunderBolt::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);
	b->EndBattleCheck();
}
Card* ThunderBolt::kreator()
{
	return new ThunderBolt();
}
ThunderBolt::~ThunderBolt()
{

}

//--------------------------------------------------------------Flamethrower-----------------------------------------------
Flamethrower::Flamethrower()
{
	Nazwa = "Flamethrower";
	Energy = 1;
	Attack = 7;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Fire;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Miotasz OGNIEM\nza 7 dmg i\n nakladasz efekt\nBURN 3 na przeciwnika";
	file_path = "resources/textures/attack_flamethrower.png";
	Set_Color_By_Type();
	update_texture();
}
Card* Flamethrower::clone() 
{
	return new Flamethrower(*this);
}
void Flamethrower::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);

	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	b->Return_Selected_Enemy()->TakeDamage(Attack + damage_modifier);

	//nakładanie efektu:
	b->Return_Selected_Enemy()->Add_Status(Status_Effect::Burn, 3);

	b->EndBattleCheck();
}
Card* Flamethrower::kreator()
{
	return new Flamethrower();
}
Flamethrower::~Flamethrower()
{

}


//--------------------------------------------------------------Earthquake-----------------------------------------------
Earthquake::Earthquake()
{
	Nazwa = "Earthquake";
	Energy = 3;
	Attack = 16;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Ground;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Wstrzasasz ziemia i\nzadajesz 18 obrazen\nWSZYSTKIM przeciwnikom";
	file_path = "resources/textures/aaa.jpg";
	Set_Color_By_Type();
	update_texture();
}
Card* Earthquake::clone() 
{
	return new Earthquake(*this);
}
void Earthquake::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);

	//zadawanie obrażeń:
	int damage_modifier = 0;
	for(auto &v : b->Return_Player()->Return_Character().Return_Status_Effects())
		if(v.first == Status_Effect::Strenght){
			damage_modifier += v.second;
		}
	for(auto &v : b->Return_Enemies()){
		v->TakeDamage(Attack + damage_modifier);
	}

	b->EndBattleCheck();
}
Card* Earthquake::kreator()
{
	return new Earthquake();
}
Earthquake::~Earthquake()
{

}


//--------------------------------------------------------------Second_Wind-----------------------------------------------
Second_Wind::Second_Wind()
{
	Nazwa = "Second Wind";
	Energy = 1;
	Shield = 5;
	Cardclass = Card_Class::Attack_Card;
	CardType = Element_Type::Air;
	//elementy graficzne:
	name = Nazwa;
	cost = std::to_string(Energy);
	text = "Bierzesz gleboki oddech.\nZyskujesz 5 tarczy\ni 1 SILY";
	file_path = "resources/textures/Excusemesir.png";
	Set_Color_By_Type();
	update_texture();
}
Card* Second_Wind::clone() 
{
	return new Second_Wind(*this);
}
void Second_Wind::Card_Effect(Battle* b)
{
	b->Return_Player()->Reduce_Energy(Energy);
	b->Return_Player()->Return_Character().Add_Shield(Shield);

	//nakładanie efektu:
	b->Return_Player()->Return_Character().Add_Status(Status_Effect::Strenght, 1);
}
Card* Second_Wind::kreator()
{
	return new Second_Wind();
}
Second_Wind::~Second_Wind()
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
	regist(8, &Flamethrower::kreator);
	regist(9, &Earthquake::kreator);
	regist(10, &Second_Wind::kreator);
}
Card* CardFactory::create_random()
{
	int g = 1 + rand() % Registered_Cards.size(); 
	return Registered_Cards[g]()->clone();
}