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
	int HP;
public:
	Character();
	Character(std::string n, int hp);
	~Character();

	std::string Return_Name();
	int Return_HP();
};
#endif