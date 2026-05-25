#ifndef BATTLE
#define BATTLE
#include "Player.h"
#include "Enemy.h"
class Player;
class Enemy;
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>

class Battle
{
protected:
	int TurnCounter = 0;
	Player *player;
	std::vector<Enemy> Battle_Enemies;
public:
	Battle();
	Battle(Player *pl, std::vector<Enemy> be);
	
	Player* Return_Player();
	std::vector<Enemy>& Return_Enemies();

	void CanPlayCardCheck();

	void EndPlayerTurn();
	void EnemyAction();
	void PlayerTurn();
	void EndBattleCheck();

	~Battle();

};
#endif
