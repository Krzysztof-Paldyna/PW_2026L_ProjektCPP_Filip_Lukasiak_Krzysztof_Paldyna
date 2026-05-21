#include "Character.h"

Character::Character()
{
	Name = "Missingno";
	HP = 10;
}
Character::Character(std::string n, int hp)
{
	Name = n;
	HP = hp;
}
std::string Character::Return_Name()
{
	return Name;
}
int Character::Return_HP()
{
	return HP;
}
Character::~Character()
{

}