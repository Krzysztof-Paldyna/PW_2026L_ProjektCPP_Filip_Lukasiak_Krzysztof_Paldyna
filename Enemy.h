#ifndef ENEMY
#define ENEMY
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "graphics_object_character.hpp"

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
public:
	PlayerCharacter();
	PlayerCharacter(std::string n, int hp);
	~PlayerCharacter();
};

class Enemy: public Character
{
protected:
	
public:
	Enemy();
	Enemy(std::string n, int hp);
	virtual ~Enemy();

	virtual void EnemyBehaviour();
};
typedef Enemy* (*EnemyCreator) (std::string n, int hp);

class BasicEnemy: public Enemy
{
public:
	BasicEnemy();
	BasicEnemy(std::string n, int hp);
	static Enemy* kreator(std::string n, int hp);
	virtual ~BasicEnemy();
	virtual void EnemyBehaviour();
};

class EnemyFactory
{
private:
	static std::map<int, EnemyCreator> Registered_Enemies;
public:
	static void regist(const int& id, EnemyCreator k);
	static Enemy* create(const int& id, std::string n, int hp);
};
#endif
