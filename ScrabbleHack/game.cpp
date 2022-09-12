#include "game.hpp"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <utility>
#include <ctype.h>
#include <fstream>


Game::Game()
{
	ScrabbleLetters Empty('.', 0);
	for (int i = 0; i < 7; i++)
	{
		PlayersLetters[i] = Empty;
	}
	int menu = 1;
	while (menu)
	{
		if (menu == 3)
		{
			enterLetters();
		}
		else if (menu == 2)
		{
			placeWord();
		}
		system("CLS");
		ScrabbleB.printBoard();
		std::cout << std::endl;
		for (int i = 0; i < 7; i++) std::cout << std::setw(3) << PlayersLetters[i] << " ";
		std::cout << std::endl;
		std::cout << "Print Board --> 1" << std::endl;
		std::cout << "Place word --> 2" << std::endl;
		std::cout << "Enter your letters --> 3" << std::endl;
		std::cout << "End --> 0" << std::endl;
		std::cout << "Enter a number: " << std::endl;
		std::cin >> menu;
	}
	
}

void Game::enterLetters()
{
	int i = 0;
	while (PlayersLetters[i].getLetter() != '.') i++;
	for (; i < 7; i++)
	{
		std::cin >> PlayersLetters[i];
	}
}

void Game::placeWord()
{
	std::cout << "Enter the word you want to place" << std::endl;
	std::string word;
	std::cin >> word;
	while (word.length() > 15 || !IsLegalWord(word))
	{
		std::cout << "Enter legal word:" << std::endl;
		std::cin >> word;
	}
	std::cout << "Enter placement of the word" << std::endl;
	int x, y;
	std::string direction;
	std::cout << "X=";
	std::cin >> x;
	std::cout << "Y=";
	std::cin >> y;
	std::cout << "Direction (DOWN/RIGHT)";
	std::cin >> direction;
	if (ScrabbleB.getLetter(7, 7) == ' ')
	{
		if (direction == "DOWN")
		{
			while (y + word.length() < 8 || x != 8)
			{
				std::cout << "Enter proper word placing tiles" << std::endl;
				std::cout << "X=";
				std::cin >> x;
				std::cout << "Y=";
				std::cin >> y;
			}
		}
		else
		{
			while (x+word.length()<8 || y!=8)
			{
				std::cout << "Enter proper word placing tiles" << std::endl;
				std::cout << "X=";
				std::cin >> x;
				std::cout << "Y=";
				std::cin >> y;
			}
		}
	}

	// coutning quantity of each letter in the word;
	int* countWord = new int[28] {0};

	// counting current users letters
	// to determine ability to place the word that they've entered
	int* countPlayer = new int[28] {0};
	for (int i = 0; i < 7; i++)
	{
		countPlayer[int(PlayersLetters[i].getLetter())-64]++;
	}

	for (int i = 0; i < word.length(); i++)
	{
		countWord[int(word[i]) - 64]++;
	}

	int missing = 0;
	for (int i = 0; i < 28; i++)
	{
		//printing Missing [amount of characters] [the character missing].

		if (countWord[i] > countPlayer[i])
		{
			missing += countWord[i] - countPlayer[i];
			std::cout << "Missing " << countWord[i] - countPlayer[i] << " " << char(i + 64) << std::endl;
			system("PAUSE");
		}
	}
	if (missing == 0)
	{
		for (int i = 0; i < word.length(); i++)
		{
			bool removeFromUser = false;
			int j = 0;
			while (!removeFromUser && j < 7)
			{
				if (PlayersLetters[j].getLetter() == toupper(word[i]))
				{
					ScrabbleLetters Empty('.', 0);
					PlayersLetters[j] = Empty;
					removeFromUser = true;
				}
				j++;
			}
			
			if (direction == "DOWN")
			{
				ScrabbleB.setLetter(ScrabbleLetters(word[i],0), y - 1 + i,x-1);
			}
			else
			{
				ScrabbleB.setLetter(ScrabbleLetters(word[i], 0), y - 1, x - 1+i);
			}
		}
		int j = 0;
		
		for (int i = 0; i < 7; i++)
		{
			if (PlayersLetters[i].getLetter() != '.')
			{
				ScrabbleLetters temp = PlayersLetters[i];
				PlayersLetters[i] = PlayersLetters[j];
				PlayersLetters[j] = temp;
				j++;
			}
		}
	}
}

bool Game::IsLegalWord(std::string& word)
{
	std::string filename = "./Words/groupedByLetters/wordsStartingWith_";
	filename += (char)toupper(word[0]);
	filename += ".txt";
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (word == line) return true;
		}
	}
	file.close();
	return false;
}
