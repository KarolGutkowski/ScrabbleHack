#include "game.hpp"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <utility>
#include <ctype.h>
#include <fstream>
#define alphabetLength 26


Game::Game()
{
	ScrabbleLetters Empty('.', 0);
	for (int i = 0; i < 7; i++)
	{
		PlayersLetters[i] = Empty;
	}
	char menu = '1';
	while (menu != '0')
	{
		if (menu == '3')
		{
			enterLetters();
		}
		else if (menu == '2')
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
	while (PlayersLetters[i].getLetter() != '.' && i<7) i++;
	for (; i < 7; i++)
	{
		std::cin >> PlayersLetters[i];
	}
}

void Game::placeWord()
{
	std::string word, direction;
	int x, y;
	enterData(word,x, y,direction);
	
	int* countWord = new int[alphabetLength] {0};
	int* countOnBoard = new int[alphabetLength] {0};
	int* countPlayer = new int[alphabetLength] {0};

	countLetters(countWord, countOnBoard, countPlayer, word,x ,y, direction);

	int missing = missingLetters(countWord, countOnBoard, countPlayer);

	if (missing == 0 && legalPlacement(word, x, y, direction, countOnBoard))
	{
		for (int i = 0; i < word.length(); i++)
		{
			bool removeFromUser = false;
			int j = 0;
			std::pair<int, int> tile;
			if (direction == "DOWN")
				tile = std::make_pair(y - 1 + i, x - 1);
			else
				tile = std::make_pair(y - 1, x - 1 + i);

			if (ScrabbleB.getLetter(tile.second, tile.first) !=word[i]) 
			{
				//std::cout << "Letter " << word[i] << " not on board" << std::endl;
				//system("PAUSE");
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
				ScrabbleB.setLetter(ScrabbleLetters(word[i], 0), tile.first, tile.second);
			}
		}
		delete[] countWord;
		delete[] countOnBoard;
		delete[] countPlayer;
		sortPlayerLetters();
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


void Game::countLetters(int* countWord, int* countOnBoard, int* countPlayer,
	std::string word, int &x, int &y ,std::string direction)
{
	for (int i = 0; i < 7; i++)
	{
		if(PlayersLetters[i].getLetter() != '.')
			countPlayer[int(PlayersLetters[i].getLetter()) - 65]++;
	}

	for (int i = 0; i < word.length(); i++)
	{
		countWord[int(word[i]) - 65]++;
	}
	for (int i = 0; i < word.length(); i++)
	{
		std::pair<int, int> tile;
		if (direction == "DOWN")
		{
			tile = std::make_pair(y - 1 + i, x - 1);
		}
		else
		{
			tile = std::make_pair(y - 1, x - 1 + i);
		}

		if (ScrabbleB.getLetter(tile.second, tile.first) != ' ')
		{
			char letter = ScrabbleB.getLetter(tile.second, tile.first);
			countOnBoard[int(ScrabbleB.getLetter(tile.second, tile.first)) - 65]++;
		}
	}
}

int Game::missingLetters(int* countWord, int* countOnBoard, int* countPlayer)
{
	int missing = 0;
	for (int i = 0; i < alphabetLength; i++)
	{
		if (countWord[i] > countPlayer[i] + countOnBoard[i])
		{
			missing += countWord[i] - countPlayer[i] - countOnBoard[i];
			std::cout << "Missing " << countWord[i] - countPlayer[i] << " " << char(i + 65) << std::endl;
			//std::cout << "There's " << countOnBoard[i] << " " << (char)(i + 65) << " on the board." << std::endl;
			system("PAUSE");
		}
		else if (countWord[i] == 0 && countOnBoard[i] != 0)
		{
			std::cout << "There are " << countOnBoard[i] << " " << char(i + 65) << "'s on the board while thre arenone in the word" << std::endl;
			std::cout << "Can not place the word in this place (1)" << std::endl;
			system("PAUSE");
			return -1;
		}
	}
	return missing;
}

void Game::sortPlayerLetters()
{
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

void Game::enterData(std::string& word, int& x, int& y, std::string& direction)
{
	std::cout << "Enter the word you want to place" << std::endl;
	std::cin >> word;
	while (word.length() > 15 || !IsLegalWord(word))
	{
		std::cout << "Enter legal word:" << std::endl;
		std::cin >> word;
	}
	std::cout << "Enter placement of the word" << std::endl;
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
			while (x + word.length() < 8 || y != 8)
			{
				std::cout << "Enter proper word placing tiles" << std::endl;
				std::cout << "X=";
				std::cin >> x;
				std::cout << "Y=";
				std::cin >> y;
			}
		}
	}
}

bool Game::legalPlacement(std::string& word, int& x, int& y, std::string &direction, int* countOnBoard)
{
	int onBoard = 0;
	for (int i = 0; i < alphabetLength; i++)
	{
		onBoard += countOnBoard[i];
	}
	if (onBoard == 0 && ScrabbleB.getLetter(7, 7) != ' ')
	{
		std::cout << "Can not place the word in this place (2)" << std::endl;
		system("PAUSE");
		return false;
	}

	for (int i = 0; i < word.length(); i++)
	{
		std::pair<int, int> tile = direction == "DOWN" ? std::make_pair(y - 1 + i, x - 1): std::make_pair(y - 1, x - 1 + i);
		/*
		if (direction == "DOWN")
			tile = std::make_pair(y - 1 + i, x - 1);
		else
			tile = std::make_pair(y - 1, x - 1 + i);
		*/
		char tileLetter = ScrabbleB.getLetter(tile.second, tile.first);
		if (tileLetter != word[i] && tileLetter != ' ')
		{
			std::cout << "Can not place the word in this place (3)" << std::endl;
			system("PAUSE");
			return false;
		}
	}

	//Checking for adjecent words
	for (int i = 0; i < word.length(); i++)
	{
		
		std::pair<int, int> tile;
		std::pair<int, int> beginAdjacentWord;
		if (direction == "DOWN")
		{
			tile = std::make_pair(y - 1 + i, x - 1);
			beginAdjacentWord = tile;
			beginAdjacentWord.second -= 1;
		}
		else
		{
			tile = std::make_pair(y - 1, x - 1 + i);
			beginAdjacentWord = tile;
			beginAdjacentWord.first -= 1;
		}
		char beginAdjacentWordLetter = ScrabbleB.getLetter(beginAdjacentWord.second, beginAdjacentWord.first);
		if (ScrabbleB.getLetter(tile.second, tile.first) == ' ')
		{
			int j = 0;
			while (beginAdjacentWordLetter != ' ')
			{
				if (direction == "DOWN")
				{
					beginAdjacentWord.second -= 1;
				}
				else
				{
					beginAdjacentWord.first -= 1;
				}
				beginAdjacentWordLetter = ScrabbleB.getLetter(beginAdjacentWord.second, beginAdjacentWord.first);
				//std::cout << beginAdjacentWordLetter << std::endl;
				//system("PAUSE");
				j++;
			}

			if (direction == "DOWN")
			{
				beginAdjacentWord.second += 1;
			}
			else
			{
				beginAdjacentWord.first += 1;
			}
			beginAdjacentWordLetter = ScrabbleB.getLetter(beginAdjacentWord.second, beginAdjacentWord.first);
			std::string adjecentWord;
			while (beginAdjacentWordLetter != ' ')
			{
				adjecentWord += beginAdjacentWordLetter;
				if (direction == "DOWN")
				{
					beginAdjacentWord.second += 1;
				}
				else
				{
					beginAdjacentWord.first += 1;
				}
				if (beginAdjacentWord.second == tile.second && beginAdjacentWord.first == tile.second)
				{
					beginAdjacentWordLetter = word[i];
				}
				else {
					beginAdjacentWordLetter = ScrabbleB.getLetter(beginAdjacentWord.second, beginAdjacentWord.first);
				}
			}
			if (!IsLegalWord(adjecentWord) && adjecentWord != "")
			{
				//std::cout << adjecentWord << std::endl;
				//system("PAUSE");
				return false;
			}
		}
	}
	
	return true;
}