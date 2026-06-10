#include "Enemy.h"
#include "Battle.h"
std::map<int, EnemyCreator> EnemyFactory::Registered_Enemies;
//-------------------------------------------------------------CharacterBaseline-----------------------------------------------
Character::Character()
{
	Name = "Missingno";
	MaxHP = 10;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
Character::Character(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
std::string Character::Return_Name()
{
	return Name;
}
int Character::Return_MaxHP()
{
	return MaxHP;
}
int Character::Return_CurrentHP()
{
	return CurrentHp;
}
void Character::Set_MaxHP(int hp)
{
	MaxHP = hp;
}
void Character::Set_CurrentHP(int hp)
{
	CurrentHp = hp;
}
int Character::Return_Shield()
{
	return Shield;
}
void Character::Add_Shield(int s)
{
	Shield += s;
}

std::vector<std::pair<Status_Effect, int>> &Character::Return_Status_Effects(){
	return status_effects;
}

std::vector<graphics_object_dmg_val> &Character::Return_Damage_Val(){
	return damage_icons;
}

void Character::Add_Status(Status_Effect effect, int val){
	for(int i = 0; i < status_effects.size(); ++i){
		if(status_effects.at(i).first == effect){
			status_effects.at(i).second += val;
			status_effect_icons.at(i) = std::make_tuple(std::get<0>(status_effect_icons.at(i)), status_effects.at(i).second, std::get<2>(status_effect_icons.at(i)));
			return;
		}
	}
	add_effect(effect, val);
	status_effects.push_back(std::make_pair(effect, val));
}

void Character::Clear_Effects(){
	status_effects.clear();
	status_effect_icons.clear();
}

void Character::Update_End_of_Turn_Effects(){
	for(int i = 0; i < status_effects.size(); ++i){
		if(status_effects.at(i).first == Status_Effect::Burn){
			TakeDamage(status_effects.at(i).second);
			--status_effects.at(i).second;
			status_effect_icons.at(i) = std::make_tuple(std::get<0>(status_effect_icons.at(i)), status_effects.at(i).second, std::get<2>(status_effect_icons.at(i)));
		}
		else if(status_effects.at(i).first == Status_Effect::Poison){
			TakeDamage(status_effects.at(i).second);
			--status_effects.at(i).second;
			status_effect_icons.at(i) = std::make_tuple(std::get<0>(status_effect_icons.at(i)), status_effects.at(i).second, std::get<2>(status_effect_icons.at(i)));
		}
		//usuwanie wyzerowanych efektów:
		if(status_effects.at(i).second <= 0){
			status_effects.erase(status_effects.begin() + i);
			status_effect_icons.erase(status_effect_icons.begin() + i);
		}
	}
}

void Character::TakeDamage(int dmg)
{
	if (Shield > 0)
	{
		if (dmg > Shield)
		{
			CurrentHp -= dmg - Shield;
			Update_Damage_Icons(Shield, false);
			Update_Damage_Icons(dmg - Shield, true);
			Shield = 0;
		}
		else
		{
			Shield -= dmg;
			Update_Damage_Icons(dmg, false);
		}
	}
	else
	{
		CurrentHp -= dmg;
		Update_Damage_Icons(dmg, true);
	}
	set_hp(CurrentHp);	//update wartości wyświetlanej
	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		isDead = true;
	}
}

void Character::Update_Damage_Icons(int dmg, bool is_HP_damage){
	std::random_device RNG;
	std::mt19937 generator(RNG());
	std::uniform_int_distribution<int> x_distribution(-80, 80);
	std::uniform_int_distribution<int> y_distribution(-10, 100);
	int pos_x = x + dim_x/2 + x_distribution(generator) - 10*std::to_string(dmg).length();
	int pos_y = y + dim_y/4 - y_distribution(generator);
	graphics_object_dmg_val dmg_icon(is_HP_damage, std::to_string(dmg), "None", 0, 0, pos_x, pos_y);
	damage_icons.push_back(dmg_icon);
	//std::cout << "size of icons vector: " << damage_icons.size() << std::endl;
}


bool Character::Return_isDead()
{
	return isDead;
}
Element_Type Character::Return_Element_Type()
{
	return CharacterType;
}
Character::~Character()
{

}
//--------------------------------------------------------------PlayerCharacter-----------------------------------------------
PlayerCharacter::PlayerCharacter()
{
	Name = "MissingnoGracz";
	MaxHP = 10;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	isEnemy = false;
	update_texture();
}
PlayerCharacter::PlayerCharacter(std::string n, int hp, Element_Type type)
{
	std::cout << "[DEBUG] Start konstruktora PlayerCharacter: " << name << std::endl;
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
	CharacterType = type;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/PlayerCharacter.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	isEnemy = false;
	update_texture();
	std::cout << "[DEBUG] Koniec konstruktora PlayerCharacter: " << name << std::endl;
}
std::string PlayerCharacter::Return_Player_Character_Description()
{
	return Charater_Description;
}
PlayerCharacter& PlayerCharacter::operator=(const PlayerCharacter& other)
{
	Name = other.Name;
	MaxHP = other.MaxHP;
	CurrentHp = MaxHP;
	CharacterType = other.CharacterType;
	//zmienne klasy graphics_object_character:
	name = other.Name;
	file_path = other.file_path;
	max_hp = other.MaxHP;
	current_hp = other.CurrentHp;
	Charater_Description = other.Charater_Description;
	isEnemy = false;
	update_texture();
	
	return *this;
}
void PlayerCharacter::Set_Character_Description(std::string desc)
{
	Charater_Description = desc;
}
void PlayerCharacter::Set_Character_File_Path(std::string p)
{
	file_path = p;
}
PlayerCharacter::~PlayerCharacter()
{

}
//--------------------------------------------------------------EnemyBaseline-----------------------------------------------
Enemy* Enemy::clone()
{
	return new Enemy(*this);
}
Enemy::Enemy()
{
	Name = "NieznanyPrzeciwnik";
	MaxHP = 100;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	Set_Intetion_Sprite(0, 6);
	update_texture();
}
void Enemy::EnemyBehaviour(Battle* battle)
{
	std::cout << "Buuuuu cos robie strasznego :3" << std::endl;
}
int Enemy::Return_Intention()
{
	return Intention;
}
void Enemy::Set_Intetion_Sprite(int I, int v)
{
	if (I == 0)
	{
    	Intetion_Image.setTexture(Attack_Texture);
		Intetion_Image.setScale(sf::Vector2f(1.0f, 1.0f));
		Intetion_Image.setTextureRect(sf::IntRect({0, 0}, {75, 75}));
		Intetion_Value_Text.setString(std::to_string(v));
	}
	else if (I == 1)
	{
    	Intetion_Image.setTexture(Shield_Texture);
		Intetion_Image.setScale(sf::Vector2f(1.0f, 1.0f));
		Intetion_Image.setTextureRect(sf::IntRect({0, 0}, {75, 75}));
		Intetion_Value_Text.setString(std::to_string(v));
	}
	else if (I == 2)
	{
		Intetion_Image.setTexture(Poison_Texture);
		Intetion_Image.setScale(sf::Vector2f(3.0f, 3.0f));
		Intetion_Image.setTextureRect(sf::IntRect({0, 0}, {25, 25}));
		Intetion_Value_Text.setString(std::to_string(v));
	}
	else if (I == 3)
	{
		Intetion_Image.setTexture(Buff_Texture);
		Intetion_Image.setScale(sf::Vector2f(3.0f, 3.0f));
		Intetion_Image.setTextureRect(sf::IntRect({0, 0}, {25, 25}));
		Intetion_Value_Text.setString(std::to_string(v));
	}
	else
	{
		std::cout<<"Zle podany argument I "<<std::endl;
	}
}
Enemy::~Enemy()
{

}
//--------------------------------------------------------------BasicEnemy-----------------------------------------------

BasicEnemy::BasicEnemy()
{
	Name = "Parobek";
	MaxHP = 18;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/BasicEnemy.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	Set_Intetion_Sprite(0, 6);
	update_texture();
}
void BasicEnemy::EnemyBehaviour(Battle* battle)
{
	if(Intention == 0)
	{
		battle->Return_Player()->Return_Character().TakeDamage(6);
		Intention = 1;
		Set_Intetion_Sprite(1, 5);
	}
	else if(Intention == 1)
	{
		Add_Shield(5);
		Intention = 0;
		Set_Intetion_Sprite(0, 6);
	}
}
Enemy* BasicEnemy::kreator()
{
	return new BasicEnemy();
}
Enemy* BasicEnemy::clone()
{
	return new BasicEnemy(*this);
}
BasicEnemy::~BasicEnemy()
{

}
//--------------------------------------------------------------JezEnemy-----------------------------------------------

Jez::Jez()
{
	Name = "Jez";
	MaxHP = 40;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::Plant;
	Shield = 10;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/JezSprite.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	Set_Intetion_Sprite(1, 10);
	update_texture();
}
void Jez::EnemyBehaviour(Battle* battle)
{
	
	if(Intention == 0)
	{
		Add_Shield(10);
		Intention = 1;
		Set_Intetion_Sprite(2, 2);
	}
	else if(Intention == 1)
	{
		battle->Return_Player()->Return_Character().Add_Status(Status_Effect::Poison, 2);
		Intention = 0;
		Set_Intetion_Sprite(1, 10);
	}
}
Enemy* Jez::kreator()
{
	return new Jez();
}
Enemy* Jez::clone()
{
	return new Jez(*this);
}
Jez::~Jez()
{

}

//--------------------------------------------------------------Oddzial_Kalmar-----------------------------------------------

SqlWard::SqlWard()
{
	Name = "GIGA Kalmar";
	MaxHP = 80;
	CurrentHp = MaxHP;
	CharacterType = Element_Type::Water;
	Shield = 15;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/Squidward.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	Set_Intetion_Sprite(3, 2);
	update_texture();
}
void SqlWard::EnemyBehaviour(Battle* battle)
{
	int dmg = 7;
	for(auto &v : status_effects){
		if(Status_Effect::Strenght == v.first){
			dmg += v.second;
		}
	}
	if(Intention == 0)
	{
		Add_Status(Status_Effect::Strenght, 2);
		Intention = 1;
		Set_Intetion_Sprite(0, dmg + 2);
	}
	else if(Intention == 1)
	{

		battle->Return_Player()->Return_Character().TakeDamage(dmg);
		Intention = 2;
		Set_Intetion_Sprite(1, 15);
	}
	else if(Intention == 2)
	{
		Add_Shield(15);
		Intention = 0;
		Set_Intetion_Sprite(3, 2);
	}
}
Enemy* SqlWard::kreator()
{
	return new SqlWard();
}
Enemy* SqlWard::clone()
{
	return new SqlWard(*this);
}
SqlWard::~SqlWard()
{

}
//--------------------------------------------------------------EnemyFactory-----------------------------------------------
void EnemyFactory::regist(const int& id, EnemyCreator k)
{
	Registered_Enemies[id] = k;
}
Enemy* EnemyFactory::create(const int& id)
{
	return Registered_Enemies[id]();
}
void EnemyFactory::Initialize()
{
	if (!Registered_Enemies.empty()) return;

	EnemyFactory::regist(1, &BasicEnemy::kreator);
	EnemyFactory::regist(2, &Jez::kreator);
	EnemyFactory::regist(3, &SqlWard::kreator);
}
Enemy* EnemyFactory::create_random()
{
	//int g = 1 + rand() % Registered_Enemies.size(); nr 3 jest bossem
	int g = 1 + rand() % 2;
	return Registered_Enemies[g]()->clone();
}