#ifndef BATTLE
#define BATTLE
#include "Player.h"
#include "Enemy.h"
#include "Card.h"
#include "graphics_object_end_turn.hpp"
#include "graphics_object_energy_counter.hpp"
#include "graphics_object_deck_info.hpp"
class Player;
class Enemy;
class Card;
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>

enum class BattleState
{
	Player_turn,
	Enemy_turn
};

class Battle
{
protected:
	int TurnCounter = 0;
	BattleState currentState = BattleState::Player_turn;
	Player *player;
	std::vector<Enemy*> Battle_Enemies;
	sf::RenderWindow *battle_window;
	sf::Font card_font;
	Card *Selected_Card = nullptr;
	int Selected_Card_Index = 0;
	Enemy *Selected_Enemy = nullptr;
	graphics_object_end_turn *end_turn_button = nullptr;
	graphics_object_energy_counter *energy_counter = nullptr;
	graphics_object_deck_info *deck_amount_info = nullptr;
	
public:
	Battle();
	Battle(Player *pl, std::vector<Enemy*> be, sf::RenderWindow *bw, graphics_object_end_turn *end, graphics_object_energy_counter *e_counter, graphics_object_deck_info *d_info);
	
	Player* Return_Player();
	std::vector<Enemy*>& Return_Enemies();

	void Render_Cards();
	void Render_Player();
	void Render_Enemies();
	void Render_End_Turn_Button();
	void Render_Card_Info_Piles();
	void Render_Energy_Counter();
	void Select_Card(int mx, int my);
	void Select_Enemy(int mx, int my);
	void Handle_Mouse_Click(int mx, int my);	//funkcja zarządza wyborem kart i ich celów oraz zmienia stan gry 

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
