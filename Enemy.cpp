#include "Enemy.h"

std::map<int, EnemyCreator> EnemyFactory::Registered_Enemies;
Enemy::Enemy()
{
	Name = "NienazwanyPrzeciwnik";
	MaxHP = 10;
	CurrentHp = MaxHP;
}
Enemy::Enemy(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
}
void Enemy::EnemyBehaviour()
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
}
BasicEnemy::BasicEnemy(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
}
void BasicEnemy::EnemyBehaviour()
{
	std::cout << "Buuuuu cos robie strasznego :3, ale jest Basic" << std::endl;
}
Enemy* BasicEnemy::kreator(std::string n, int hp)
{
	return new BasicEnemy(n, hp);
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