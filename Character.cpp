#include "Character.h"

Character::Character()
{
	Name = "Missingno";
	MaxHP = 10;
	CurrentHp = MaxHP;
}
Character::Character(std::string n, int hp)
{
	Name = n;
	MaxHP = hp;
	CurrentHp = MaxHP;
}
std::string Character::Return_Name()
{
	return Name;
}
int Character::Return_MaxHP()
{
	return MaxHP;
}
int Character::Return_CurrentHP()
{
	return CurrentHp;
}
void Character::Set_MaxHP(int hp)
{
	MaxHP = hp;
}
void Character::Set_CurrentHP(int hp)
{
	CurrentHp = hp;
}
Character::~Character()
{

}