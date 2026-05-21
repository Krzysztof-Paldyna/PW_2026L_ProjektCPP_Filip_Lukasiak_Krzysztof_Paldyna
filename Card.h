#ifndef CARD
#define CARD
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <vector>

class Card
{
protected:
	std::string Nazwa;
	int Energy;
public:
	Card(std::string n, int e);
	~Card();
};
#endif
