#include "game.hpp"
#include <iostream>
#include <stdlib.h>
#include <iomanip>

Game::Game()
{
	ScrabbleLetters Empty(' ', 0);
	for (int i = 0; i < 7; i++)
	{
		PlayersLetters[i] = Empty;
	}
	Board ScrabbleB;
	int menu = 1;
	while (menu)
	{
		if (menu == 4) enterLetters();
		system("CLS");
		ScrabbleB.printBoard();
		std::cout << std::endl;
		for (int i = 0; i < 7; i++) std::cout << std::setw(3) << PlayersLetters[i] << " ";
		std::cout << std::endl;
		std::cout << "Print Board --> 1" << std::endl;
		std::cout << "Place letter --> 2" << std::endl;
		std::cout << "Place word --> 3" << std::endl;
		std::cout << "Enter your letters --> 4" << std::endl;
		std::cout << "End --> 0" << std::endl;
		std::cout << "Enter a number: " << std::endl;
		std::cin >> menu;
	}
	
}

void Game::enterLetters()
{
	int i = 0;
	while (PlayersLetters[i].getLetter() != ' ') i++;
	for (; i < 7; i++)
	{
		std::cin >> PlayersLetters[i];
	}
}