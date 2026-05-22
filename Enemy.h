#ifndef ENEMY
#define ENEMY
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

class Enemy
{
protected:
	std::string Name;
	int MaxHP;
	int CurrentHp;
public:
	Enemy();
	Enemy(std::string n, int hp);
	virtual ~Enemy();

	std::string Return_Name();
	int Return_MaxHP();
	int Return_CurrentHP();
	void Set_CurrentHP(int hp);
	void Set_MaxHP(int hp);

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
