#include "Character.h"
#include "Player.h"
#include "Card.h"
int main()
{
	
	Character g("Pimpek", 20);
	Card Push("Push", 2);

	Player Gracz;
	Gracz.Set_Character(g);

	std::cout << g.Return_Name() << " " << g.Return_HP() << std::endl;
	return 0;
}