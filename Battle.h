#ifndef BATTLE
#define BATTLE
#include "Player.h"
#include "Enemy.h"
#include "Card.h"
class Player;
class Enemy;
class Card;
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>

class Battle
{
protected:
	int TurnCounter = 0;
	Player *player;
	std::vector<Enemy> Battle_Enemies;
	sf::RenderWindow *battle_window;
	sf::Font card_font;
	Card *Selected_Card = nullptr;
	int Selected_Card_Index = 0;
	Enemy *Selected_Enemy = nullptr;

public:
	Battle();
	Battle(Player *pl, std::vector<Enemy> be, sf::RenderWindow *bw);
	
	Player* Return_Player();
	std::vector<Enemy>& Return_Enemies();

	void Render_Cards();
	void Render_Player();
	void Render_Enemies();
	void Select_Card(int mx, int my);
	void Select_Enemy(int mx, int my);
	void Handle_Mouse_Click(int mx, int my);

	void CanPlayCardCheck(); //Konsola
	void CanPlayCardCheck2(Card *c, Enemy *e, int i); //Okno

	void EndPlayerTurn();
	void EnemyAction();
	void PlayerTurn();
	void EndBattleCheck();

	Enemy* &Return_Selected_Enemy();

	~Battle();

};
#endif
