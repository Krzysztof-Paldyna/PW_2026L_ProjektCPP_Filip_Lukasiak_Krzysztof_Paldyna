#include "Player.h"

Player::Player()
{
	std::cout << "[DEBUG] Start konstruktora Player" << std::endl;
	Max_Energy = 3;
	Current_Energy = Max_Energy;
	Hand_Size = 4;
	std::cout << "[DEBUG] koniec konstruktora Player" << std::endl;
}
Player::~Player()
{
}
void Player::Set_Character(PlayerCharacter c)
{
	Player_Char = c;
}
void Player::Add_Card(Card* c)
{
	PlayerDeck.push_back(c->clone());
}
PlayerCharacter& Player::Return_Character()
{
	return Player_Char;
}
std::vector<Card*> &Player::Return_PlayerDeck()
{
	return PlayerDeck;
}
std::vector<Card*> &Player::Return_PlayerHand()
{
	return HandCards;
}
std::vector<Card*> &Player::Return_DiscardDeck()
{
	return DiscardDeck;
}
void Player::All_Cards()
{
	for (int i = 0; i < PlayerDeck.size(); i++)
	{
		std::cout << i <<" --- " << PlayerDeck.at(i)->Return_Card_Name() << std::endl;
	}
}
void Player::All_Discard_Cards()
{
	for (int i = 0; i < DiscardDeck.size(); i++)
	{
		std::cout << i << " --- " << DiscardDeck.at(i)->Return_Card_Name() << std::endl;
	}
}
void Player::All_Hand_Cards()
{
	for (int i = 0; i < HandCards.size(); i++)
	{
		std::cout << i << " --- " << HandCards.at(i)->Return_Card_Name() << std::endl;
	}
}
Card* Player::PlayCard(int g)
{
	DiscardDeck.push_back(HandCards.at(g));
	Card* pc = HandCards.at(g);
	HandCards.erase(HandCards.begin() + g);
	return pc;
}
void Player::Discard_Card_From_Hand(int g)
{
	DiscardDeck.push_back(HandCards.at(g));
	HandCards.erase(HandCards.begin() + g);
}
void Player::Discard_Card_From_Deck(int g)
{
	DiscardDeck.push_back(PlayerDeck.at(g));
	PlayerDeck.erase(PlayerDeck.begin() + g);
}
void Player::Return_Discarded_Cards_to_Deck()
{
	while(DiscardDeck.size() != 0)
	{
		PlayerDeck.push_back(DiscardDeck.at(0));
		DiscardDeck.erase(DiscardDeck.begin() + 0);
	}
}
void Player::SetHand()
{
	if (Hand_Size <= PlayerDeck.size() && !PlayerDeck.empty())
	{
		for (int i = 0; i < Hand_Size; i++)
		{
			int g;
			if(PlayerDeck.size() > 0)
			{
				g = rand() % PlayerDeck.size();
				HandCards.push_back(PlayerDeck.at(g));
				PlayerDeck.erase(PlayerDeck.begin() + g);
			}
			else
			{
				g = 0;
				HandCards.push_back(PlayerDeck.at(g));
				PlayerDeck.erase(PlayerDeck.begin() + g);
			}
		}
	}
	else
	{
		for (int i = 0; i <= PlayerDeck.size(); i++)
		{
			HandCards.push_back(PlayerDeck.at(0));
			PlayerDeck.erase(PlayerDeck.begin());
		}
	}
}
void Player::Give_Card_to_Hand(int g)
{
	HandCards.push_back(PlayerDeck.at(g));
	PlayerDeck.erase(PlayerDeck.begin() + g);
}
void Player::Give_Random_Card_to_Hand()
{
	if(PlayerDeck.size() == 0 && DiscardDeck.size() == 0)
	{
		std::cout<<"Tak nie powinno byc, jak to zrobiles ze masz tak malo kart xpp?"<<std::endl;
	}
	else
	{
		if(PlayerDeck.size() == 0)
		{
			Return_Discarded_Cards_to_Deck();
		}
		int g;
		if(PlayerDeck.size() > 0)
		{
			g = rand() % PlayerDeck.size();
			HandCards.push_back(PlayerDeck.at(g));
			PlayerDeck.erase(PlayerDeck.begin() + g);
			
		}
		else
		{
			g = 0;
			HandCards.push_back(PlayerDeck.at(g));
			PlayerDeck.erase(PlayerDeck.begin() + g);
		}
	}
}
void Player::RerollHand()
{
	while (HandCards.size() != 0)
	{
		DiscardDeck.push_back(HandCards.at(0));
		HandCards.erase(HandCards.begin() + 0);
	}
	if (PlayerDeck.size() < Hand_Size)
	{
		Return_Discarded_Cards_to_Deck();
	}
	SetHand();
}
int Player::Return_Max_Energy()
{
	return Max_Energy;
}
int Player::Return_Current_Energy()
{
	return Current_Energy;
}
void Player::Add_Energy(int e)
{
	Current_Energy += e;
}
void Player::Reduce_Energy(int e)
{
	Current_Energy -= e;
}
void Player::Reset_Energy()
{
	Current_Energy = Max_Energy;
}
void Player::Set_Hand_Size(int s)
{
	Hand_Size = s;
}