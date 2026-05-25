#include "Player.h"
#include "Card.h"
#include "Enemy.h"
#include "Battle.h"
int main()
{
	srand(time(NULL));
	//-------------------------------------
	CardFactory::regist(1, &AttackCard::kreator);
	CardFactory::regist(2, &ShieldCard::kreator);
	CardFactory::regist(3, &AttackShieldCard::kreator);
	
	Card* BasicAttack = CardFactory::create(1, "BasicAttack", 1);
	Card* BasicShield = CardFactory::create(2, "BasicShield", 1);
	Card* BasicAttackShield = CardFactory::create(3, "BasicAttackShield", 1);
	//-------------------------------------

	//-------------------------------------
	EnemyFactory::regist(1, &BasicEnemy::kreator);

	Enemy* BasicEnemy = EnemyFactory::create(1, "BasicEnemy", 25);
	std::vector<Enemy> Act_Enemies;
	Act_Enemies.push_back(*BasicEnemy);
	//-------------------------------------

	PlayerCharacter g("Pimpek", 20);
	
	//-------------------------------------
	Player Gracz;
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicAttackShield);
	Gracz.Add_Card(BasicAttackShield);
	Gracz.Set_Character(g);
	//-------------------------------------
	Battle b(&Gracz, Act_Enemies);
	b.PlayerTurn();
	
	return 0;
}