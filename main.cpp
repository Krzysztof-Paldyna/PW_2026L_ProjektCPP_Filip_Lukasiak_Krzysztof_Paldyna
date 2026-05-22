#include "Character.h"
#include "Player.h"
#include "Card.h"
#include "Enemy.h"
int main()
{
	//-------------------------------------
	CardFactory::regist(1, &AttackCard::kreator);
	CardFactory::regist(2, &ShieldCard::kreator);
	
	Card* BasicAttack = CardFactory::create(1, "BasicAttack", 1);
	Card* BasicShield = CardFactory::create(2, "BasicShield", 1);
	//-------------------------------------

	//-------------------------------------
	EnemyFactory::regist(1, &BasicEnemy::kreator);

	Enemy* BasicEnemy = EnemyFactory::create(1, "BasicEnemy", 25);
	//-------------------------------------

	Character g("Pimpek", 20);
	

	Player Gracz;
	Gracz.Add_Card(*BasicAttack);
	Gracz.Set_Character(g);

	std::cout << g.Return_Name() << " " << g.Return_MaxHP() << std::endl;
	return 0;
}