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
	std::vector<Enemy> Battle_Enemies;
public:
	Battle();
	Battle(std::string n, int hp);
	~Battle();

};
#endif
