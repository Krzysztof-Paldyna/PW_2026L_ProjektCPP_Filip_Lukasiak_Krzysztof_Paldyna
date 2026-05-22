#ifndef CHARACTER
#define CHARACTER
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>

class Character
{
protected:
	std::string Name;
	int MaxHP;
	int CurrentHp;
public:
	Character();
	Character(std::string n, int hp);
	~Character();

	std::string Return_Name();
	int Return_MaxHP();
	int Return_CurrentHP();
	void Set_CurrentHP(int hp);
	void Set_MaxHP(int hp);
};
#endif