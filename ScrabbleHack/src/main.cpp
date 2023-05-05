#include <iostream>
#include "game.hpp"
#include <locale.h>


int main()
{
	setlocale(LC_CTYPE, "Polish");
	Game Scrabble1;
	Scrabble1.Start();
	return 0;
}