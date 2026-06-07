#include "Enemy.h"
#include "Battle.h"
std::map<int, EnemyCreator> EnemyFactory::Registered_Enemies;
//-------------------------------------------------------------CharacterBaseline-----------------------------------------------
Character::Character()
{
	Name = "Missingno";
	MaxHP = 10;
	CurrentHp = MaxHP;
	CharacterType = None;
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
	CharacterType = None;
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

std::vector<graphics_object_dmg_val> &Character::Return_Damage_Val(){
	return damage_icons;
}
void Character::TakeDamage(int dmg)
{
	std::random_device RNG;
	std::mt19937 generator(RNG());
	std::uniform_int_distribution<int> x_distribution(-80, 80);
	std::uniform_int_distribution<int> y_distribution(-10, 100);
	int pos_x = x + dim_x/2 + x_distribution(generator) - 10*std::to_string(dmg).length();
	int pos_y = y + dim_y/4 - y_distribution(generator);
	graphics_object_dmg_val dmg_icon(std::to_string(dmg), "None", 0, 0, pos_x, pos_y);
	damage_icons.push_back(dmg_icon);
	//std::cout << "size of icons vector: " << damage_icons.size() << std::endl;

	if (Shield > 0)
	{
		if (dmg > Shield)
		{
			CurrentHp -= dmg - Shield;
			Shield = 0;
		}
		else
		{
			Shield -= dmg;
		}
	}
	else
	{
		CurrentHp -= dmg;
	}
	set_hp(CurrentHp);	//update wartości wyświetlanej
	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		isDead = true;
	}
}
bool Character::Return_isDead()
{
	return isDead;
}
ElementType Character::Return_Element_Type()
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
	CharacterType = None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	isEnemy = false;
	update_texture();
}
PlayerCharacter::PlayerCharacter(std::string n, int hp)
{
	std::cout << "[DEBUG] Start konstruktora PlayerCharacter: " << name << std::endl;
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
	CharacterType = None;
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
	CharacterType = None;
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
		Intetion_Value_Text.setString(std::to_string(v));
	}
	else if (I == 1)
	{
    	Intetion_Image.setTexture(Shield_Texture);
		Intetion_Value_Text.setString("");
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
	CharacterType = None;
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
		Set_Intetion_Sprite(1, 0);
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
	CharacterType = Plant;
	Shield = 10;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/JezSprite.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
	Set_Intetion_Sprite(1, 0);
	update_texture();
}
void Jez::EnemyBehaviour(Battle* battle)
{
	
	if(Intention == 0)
	{
		Add_Shield(10);
		Intention = 1;
		Set_Intetion_Sprite(0, 2);
	}
	else if(Intention == 1)
	{
		battle->Return_Player()->Return_Character().TakeDamage(2);
		Intention = 0;
		Set_Intetion_Sprite(1, 0);
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
}
Enemy* EnemyFactory::create_random()
{
	int g = 1 + rand() % Registered_Enemies.size(); 
	return Registered_Enemies[g]()->clone();
}