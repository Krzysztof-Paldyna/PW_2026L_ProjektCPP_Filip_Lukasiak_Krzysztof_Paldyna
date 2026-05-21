#include "Player.h"

Player::Player()
{
}
Player::~Player()
{
}
void Player::Set_Character(Character c)
{
	Player_Char = c;
}
void Player::Add_Card(Card c)
{
	PlayerDeck.push_back(c);
}