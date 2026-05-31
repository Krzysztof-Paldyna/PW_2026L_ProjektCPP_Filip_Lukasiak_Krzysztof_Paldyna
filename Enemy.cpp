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
void Character::TakeDamage(int dmg)
{
	CurrentHp -= dmg;
	set_hp(CurrentHp);
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
}
PlayerCharacter::PlayerCharacter(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
	CharacterType = None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/PlayerCharacter.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
PlayerCharacter::~PlayerCharacter()
{

}
//--------------------------------------------------------------EnemyBaseline-----------------------------------------------
Enemy::Enemy()
{
	Name = "NienazwanyPrzeciwnik";
	MaxHP = 10;
	CurrentHp = MaxHP;
	CharacterType = None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
Enemy* Enemy::clone()
{
	return new Enemy(*this);
}
Enemy::Enemy(std::string n, int hp)
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
void Enemy::EnemyBehaviour(Battle* battle)
{
	std::cout << "Buuuuu cos robie strasznego :3" << std::endl;
}
Enemy::~Enemy()
{

}
//--------------------------------------------------------------BasicEnemy-----------------------------------------------
BasicEnemy::BasicEnemy()
{
	Name = "NienazwanyBasicEnemy";
	MaxHP = 10;
	CurrentHp = MaxHP;
	CharacterType = None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "None";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
BasicEnemy::BasicEnemy(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
	CharacterType = None;
	//zmienne klasy graphics_object_character:
	name = Name;
	file_path = "resources/textures/BasicEnemy.png";
	max_hp = MaxHP;
	current_hp = CurrentHp;
}
void BasicEnemy::EnemyBehaviour(Battle* battle)
{
	std::cout << "Buuuuu cos robie strasznego :3, ale jest Basic" << std::endl;
	battle->Return_Player()->Return_Character().TakeDamage(2);
}
Enemy* BasicEnemy::kreator(std::string n, int hp)
{
	return new BasicEnemy(n, hp);
}
Enemy* BasicEnemy::clone()
{
	return new BasicEnemy(*this);
}
BasicEnemy::~BasicEnemy()
{

}
//--------------------------------------------------------------EnemyFactory-----------------------------------------------
void EnemyFactory::regist(const int& id, EnemyCreator k)
{
	Registered_Enemies[id] = k;
}
Enemy* EnemyFactory::create(const int& id, std::string n, int hp)
{
	return Registered_Enemies[id](n, hp);
}