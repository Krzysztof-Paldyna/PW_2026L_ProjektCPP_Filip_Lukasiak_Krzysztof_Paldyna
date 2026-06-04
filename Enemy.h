#ifndef ENEMY
#define ENEMY
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "graphics_object_character.hpp"

class Battle;

enum ElementType
{
	None= 0,
	Fire,
	Water,
	Wind,
	Ground, 
	Plant,
	Electric,
	Ice
};

class Character : public graphics_object_character
{
protected:
	std::string Name;
	int MaxHP;
	int CurrentHp;
	int Shield = 0;
	bool isDead = false;
	ElementType CharacterType;
public:
	Character();
	Character(std::string n, int hp);
	~Character();

	std::string Return_Name();
	int Return_MaxHP();
	int Return_CurrentHP();
	void Set_CurrentHP(int hp);
	void Set_MaxHP(int hp);
	void Add_Shield(int s);
	int Return_Shield();
	bool Return_isDead();

	void TakeDamage(int dmg);

};
class PlayerCharacter : public Character
{
private:
	std::string Charater_Description;
public:
	PlayerCharacter();
	PlayerCharacter(std::string n, int hp);
	void Set_Character_Description(std::string desc);
	void Set_Character_File_Path(std::string p);
	std::string Return_Player_Character_Description();
	PlayerCharacter& operator=(const PlayerCharacter& other);
	~PlayerCharacter();
};

class Enemy: public Character
{
protected:
	
public:
	Enemy();
	Enemy(std::string n, int hp);
	virtual Enemy* clone();
	virtual ~Enemy();

	virtual void EnemyBehaviour(Battle* battle);
};
typedef Enemy* (*EnemyCreator) (std::string n, int hp);

class BasicEnemy: public Enemy
{
public:
	BasicEnemy();
	BasicEnemy(std::string n, int hp);
	static Enemy* kreator(std::string n, int hp);
	virtual Enemy* clone();
	virtual ~BasicEnemy();
	virtual void EnemyBehaviour(Battle* battle);
};

class EnemyFactory
{
private:
	static std::map<int, EnemyCreator> Registered_Enemies;
public:
	static void Initialize(); 
	static void regist(const int& id, EnemyCreator k);
	static Enemy* create(const int& id, std::string n, int hp);
};
#endif
