#include "Battle.h"

Battle::Battle()
{
	
	player = new Player;
	player_character = player->Return_Character();
}
Battle::Battle(Player* pl, std::vector<Enemy> be)
{
	player = pl;
	Battle_Enemies = be;
	player_character = player->Return_Character();
}
void Battle::StartBattle()
{
	bool g = true;
	int tt;
	std::cout << "Zaczynamy walke " << player_character.Return_Name() << " vs ";
	std::cout << Battle_Enemies.at(0).Return_Name();
	for (int i = 1; i < Battle_Enemies.size(); i++)
	{
		std::cout <<" & " << Battle_Enemies.at(i).Return_Name() << " ";
	}
	std::cout << std::endl;
	player->SetHand();
	while (g == true)
	{
		std::cout << "Co chcesz zrobic? " << std::endl;
		std::cout << " 0 --- jakie mam karty w stosie" << std::endl;
		std::cout << " 1 --- jakie mam karty w rece" << std::endl;
		std::cout << " 2 --- jakie mam discarded karty " << std::endl;
		std::cout << " 3 --- zagraj karte " << std::endl;
		std::cout << " 4 --- reset discarded sterty " << std::endl;
		std::cin >> tt;
		switch (tt)
		{
		case 0:
		{
			player->All_Cards();
			break;
		}
		case 1:
		{
			player->All_Hand_Cards();
			break;
		}
		case 2:
		{
			player->All_Discard_Cards();
			break;
		}
		case 3:
		{
			player->PlayCard()->Card_Effect();
			break;
		}
		default:
		{
			std::cout << "Zla opcja" << std::endl;
			continue;
		}
		}
	}
}
Battle::~Battle()
{

}