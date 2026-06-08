#ifndef ENEMY
#define ENEMY
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <map>
#include "graphics_object_character.hpp"
#include "graphics_object_damage_val.hpp"

class Battle;

enum class Element_Type
{
	None= 0,
	Fire,
	Water,
	Air,
	Ground, 
	Plant,
	Electric,
	Metal
};

class Character : public graphics_object_character
{
protected:
	std::string Name;
	int MaxHP;
	int CurrentHp;
	int Shield = 0;
	bool isDead = false;
	Element_Type CharacterType;
	std::vector<std::pair<Status_Effect, int>> status_effects;
	std::vector<graphics_object_dmg_val> damage_icons;
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
	std::vector<std::pair<Status_Effect, int>> &Return_Status_Effects();
	std::vector<graphics_object_dmg_val> &Return_Damage_Val();
	Element_Type Return_Element_Type();

	void Add_Status(Status_Effect effect, int val);
	void Clear_Effects();
	void Update_End_of_Turn_Effects();
	void TakeDamage(int dmg);
	void Update_Damage_Icons(int dmg, bool is_HP_damage);
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
	int Intention = 0;

public:
	Enemy();
	virtual Enemy* clone();
	virtual ~Enemy();
	virtual void EnemyBehaviour(Battle* battle);

	int Return_Intention();
	void Set_Intetion_Sprite(int I, int v);
};
typedef Enemy* (*EnemyCreator) ();

class BasicEnemy: public Enemy
{
public:
	BasicEnemy();
	static Enemy* kreator();
	virtual Enemy* clone();
	virtual ~BasicEnemy();
	virtual void EnemyBehaviour(Battle* battle);
};

class Jez: public Enemy
{
public:
	Jez();
	static Enemy* kreator();
	virtual Enemy* clone();
	virtual ~Jez();
	virtual void EnemyBehaviour(Battle* battle);
};

class EnemyFactory
{
private:
	static std::map<int, EnemyCreator> Registered_Enemies;
public:
	static void Initialize(); 
	static void regist(const int& id, EnemyCreator k);
	static Enemy* create(const int& id);
	static Enemy* create_random();
};
#endif
