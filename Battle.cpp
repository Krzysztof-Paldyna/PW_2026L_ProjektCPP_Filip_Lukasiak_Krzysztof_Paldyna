#include "Battle.h"

Battle::Battle()
{
	player = new Player;
}
Battle::Battle(Player* pl, std::vector<Enemy> be)
{
	player = pl;
	Battle_Enemies = be;
	player->SetHand();
}
void Battle::PlayerTurn()
{
	bool g = true;
	int tt;
	while (g == true)
	{
		std::cout << "Aktualna Energia: " << player->Return_Current_Energy() << "/" << player->Return_Max_Energy() << std::endl;
		std::cout << "Aktualna Tarcza: " << player->Return_Character().Return_Shield() << std::endl;
		std::cout << std::endl;
		std::cout << "Tura nr:." << TurnCounter << std::endl;
		std::cout << std::endl;
		std::cout << player->Return_Character().Return_Name() << " " << player->Return_Character().Return_CurrentHP()<<"/"<< player->Return_Character().Return_MaxHP() << " ";
		std::cout << Battle_Enemies.at(0).Return_Name() << " " << Battle_Enemies.at(0).Return_CurrentHP() << "/" << Battle_Enemies.at(0).Return_MaxHP();
		for (int i = 1; i < Battle_Enemies.size(); i++)
		{
			std::cout << " & " << Battle_Enemies.at(i).Return_Name() << " " << Battle_Enemies.at(i).Return_CurrentHP() << "/" << Battle_Enemies.at(i).Return_MaxHP();
		}
		std::cout << std::endl;
		std::cout << "Co chcesz zrobic? " << std::endl;
		std::cout << " 0 --- jakie mam karty w stosie" << std::endl;
		std::cout << " 1 --- jakie mam karty w rece" << std::endl;
		std::cout << " 2 --- jakie mam discarded karty " << std::endl;
		std::cout << " 3 --- zagraj karte " << std::endl;
		std::cout << " 4 --- skoncz ture " << std::endl;
		std::cin >> tt;
		switch (tt)
		{
		case 0:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Cards();
			break;
		}
		case 1:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Hand_Cards();
			break;
		}
		case 2:
		{
			std::cout << "\033[2J\033[1;1H";
			player->All_Discard_Cards();
			break;
		}
		case 3:
		{
			std::cout << "\033[2J\033[1;1H";
			CanPlayCardCheck();
			break;
		}
		case 4:
		{
			std::cout << "\033[2J\033[1;1H";
			EndPlayerTurn();
		}
		default:
		{
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Zla opcja" << std::endl;
			continue;
		}
		}
	}
}
void Battle::EndPlayerTurn()
{
	player->Reset_Energy();
	player->RerollHand();
	EnemyAction();
}
void Battle::EnemyAction()
{
	for (int i = 0; i < Battle_Enemies.size(); i++)
	{
		Battle_Enemies.at(i).EnemyBehaviour();
	}
	TurnCounter += 1;
	PlayerTurn();
}
std::vector<Enemy>& Battle::Return_Enemies()
{
	return Battle_Enemies;
}
void Battle::CanPlayCardCheck()
{
	int g;
	std::cout << "Jaka karte chcesz zagrac? " << std::endl;
	player->All_Hand_Cards();
	std::cin >> g;
	if (player->Return_Current_Energy() >= player->Return_PlayerHand().at(g)->Return_Card_Cost())
	{
		player->PlayCard(g)->Card_Effect(this);
	}
	else
	{
		std::cout << "Nie masz energii by zagrac te karte :( " << std::endl;
	}
}
Player* Battle::Return_Player()
{
	return player;
}
Battle::~Battle()
{

}