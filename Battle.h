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
	Player *player;
	Character player_character;
	std::vector<Enemy> Battle_Enemies;
public:
	Battle();
	Battle(Player *pl, std::vector<Enemy> be);
	
	void StartBattle();

	~Battle();

};
#endif
