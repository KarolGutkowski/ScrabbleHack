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
	points = 0;
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
		else if (menu == '4')
		{
			otherPlayerWord();
		}
		else if (menu == '5')
		{
			giveBestWord();
		}
 		system("CLS");
		ScrabbleB.printBoard();
		std::cout << std::endl;
		for (int i = 0; i < 7; i++) std::cout << std::setw(3) << PlayersLetters[i] << " ";
		std::cout << std::endl;
		std::cout << "You have " << points << " points" << std::endl;
		std::cout << "Print Board --> 1" << std::endl;
		std::cout << "Place word --> 2" << std::endl;
		std::cout << "Enter your letters --> 3" << std::endl;
		std::cout << "Enter other players word --> 4" << std::endl;
		std::cout << "Give me best word to place --> 5" << std::endl;
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
	int currentWordPoints = 0;
	std::string word, direction;
	int x, y, countBlanks=0;
	enterData(word,x, y,direction);
	if (word == "0") return;
	int* countWord = new int[alphabetLength] {0};
	int* countOnBoard = new int[alphabetLength] {0};
	int* countPlayer = new int[alphabetLength] {0};

	countLetters(countWord, countOnBoard, countPlayer, word,x ,y, direction, countBlanks);

	int missing = missingLetters(countWord, countOnBoard, countPlayer,countBlanks);
	int adjecentWordPoints = 0;

	if (missing <= countBlanks)
	{
		for (int i = 0; i < alphabetLength; i++)
		{
			while (countWord[i] > countPlayer[i] + countOnBoard[i])
			{
				int j = 0;
				while (PlayersLetters[j].getLetter() != '*' && j < 7) j++;
				PlayersLetters[j] = ScrabbleLetters(char(i + 65), 0);
				countBlanks--;
				countPlayer[i]++;
				missing--;
			}
		}
	}
	if (missing == 0 && legalPlacement(word, x, y, direction, countOnBoard, adjecentWordPoints))
	{
		int wordMultiplier = 1;
		for (int i = 0; i < word.length(); i++)
		{
			bool removeFromUser = false;
			int j = 0;
			std::pair<int, int> tile;
			if (direction == "DOWN")
				tile = std::make_pair(y - 1 + i, x - 1);
			else
				tile = std::make_pair(y - 1, x - 1 + i);

			if (ScrabbleB.getLetter(tile.second, tile.first) == ' ')
			{
				int letterPoints = 0;
				while (!removeFromUser && j<7)
				{
					if (PlayersLetters[j].getLetter() == toupper(word[i]))
					{
						letterPoints = PlayersLetters[j].getPoints();
						int bonusAmount = ScrabbleB.getBonus(tile.second, tile.first);
						if (ScrabbleB.getBonusType(tile.second, tile.first) == 'S')
						{
							wordMultiplier *= bonusAmount;
							currentWordPoints += letterPoints;
						}
						else
						{
							currentWordPoints += letterPoints * bonusAmount;
						}
						ScrabbleLetters Empty('.', 0);
						PlayersLetters[j] = Empty;
						removeFromUser = true;
					}
					j++;
				}
				ScrabbleB.setLetter(ScrabbleLetters(word[i], letterPoints), tile.first, tile.second);
			}
			else
			{
				currentWordPoints += ScrabbleB.getScrabbleLetter(tile.second, tile.first).getPoints();
			}
		}
		points += currentWordPoints * wordMultiplier;
		points += adjecentWordPoints;
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
	std::string word, int x, int y ,std::string direction, int& countBlanks)
{
	countWordLetters(countWord, word);
	countPlayerLetters(countPlayer,countBlanks);
	countBoardLetters(countOnBoard, word, x, y, direction);
}

int Game::missingLetters(int* countWord, int* countOnBoard, int* countPlayer, int countBlanks)
{
	int missing = 0;
	for (int i = 0; i < alphabetLength; i++)
	{
		if (countWord[i] > countPlayer[i] + countOnBoard[i])
		{
			missing += countWord[i] - countPlayer[i] - countOnBoard[i];
			//std::cout << "Missing " << countWord[i] - countPlayer[i] << " " << char(i + 65) << std::endl;
			//std::cout << "There's " << countOnBoard[i] << " " << (char)(i + 65) << " on the board." << std::endl;
			//system("PAUSE");
		}
		else if (countWord[i] == 0 && countOnBoard[i] != 0)
		{
			//std::cout << "There are " << countOnBoard[i] << " " << char(i + 65) << "'s on the board while thre arenone in the word" << std::endl;
			//std::cout << "Can not place the word in this place (1)" << std::endl;
			//system("PAUSE");
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
	std::cout << "Want to go back? press 0 and enter :)" << std::endl;
	std::cin >> word;
	if (word == "0") return;
	while (word.length() > 15 || !IsLegalWord(word))
	{
		std::cout << "Enter legal word:" << std::endl;
		std::cout << "Want to go back? press 0 and enter :)" << std::endl;
		std::cin >> word;
		if (word == "0") return;
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

bool Game::legalPlacement(std::string& word, int& x, int& y, std::string &direction, int* countOnBoard,int& adjecentWordPoints)
{
	try {
		int onBoard = 0;
		for (int i = 0; i < alphabetLength; i++)
		{
			onBoard += countOnBoard[i];
		}
		if (onBoard == 0 && ScrabbleB.getLetter(7, 7) != ' ')
		{
			//std::cout << "Can not place the word in this place (2)" << std::endl;
			//system("PAUSE");
			return false;
		}

		for (int i = 0; i < word.length(); i++)
		{
			std::pair<int, int> tile = direction == "DOWN" ? std::make_pair(y - 1 + i, x - 1) : std::make_pair(y - 1, x - 1 + i);
			/*
			if (direction == "DOWN")
				tile = std::make_pair(y - 1 + i, x - 1);
			else
				tile = std::make_pair(y - 1, x - 1 + i);
			*/
			char tileLetter = ScrabbleB.getLetter(tile.second, tile.first);
			if (tileLetter != word[i] && tileLetter != ' ')
			{
				//std::cout << "Can not place the word in this place (3)" << std::endl;
				//system("PAUSE");
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
				ScrabbleLetters currentScrabble = ScrabbleB.getScrabbleLetter(beginAdjacentWord.second, beginAdjacentWord.first);
				beginAdjacentWordLetter = currentScrabble.getLetter();
				adjecentWordPoints += currentScrabble.getPoints();
				int adjecentWordMultiplier = 1;
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
					if (beginAdjacentWord.second == tile.second && beginAdjacentWord.first == tile.first)
					{
						currentScrabble = ScrabbleLetters(word[i]);
						beginAdjacentWordLetter = currentScrabble.getLetter();
						if (ScrabbleB.getBonusType(beginAdjacentWord.second, beginAdjacentWord.first) == 'S')
						{
							adjecentWordMultiplier *= ScrabbleB.getBonus(beginAdjacentWord.second, beginAdjacentWord.first);
							adjecentWordPoints += currentScrabble.getPoints();
						}
						else
						{
							adjecentWordPoints += currentScrabble.getPoints() * ScrabbleB.getBonus(beginAdjacentWord.second, beginAdjacentWord.first);
						}
					}
					else {
						currentScrabble = ScrabbleB.getScrabbleLetter(beginAdjacentWord.second, beginAdjacentWord.first);
						beginAdjacentWordLetter = currentScrabble.getLetter();
						adjecentWordPoints += currentScrabble.getPoints();
					}
				}
				//adjecentWordPoints = 0;
				if (!IsLegalWord(adjecentWord) && adjecentWord != "")
				{
					return false;
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return true;
}


void Game::otherPlayerWord()
{
	std::string word, direction;
	int x, y;
	enterData(word,x,y,direction);
	if (word == "") return;
	int* countWord = new int[alphabetLength] {0};
	int* countOnBoard = new int[alphabetLength] {0};
	countWordLetters(countWord, word);
	countBoardLetters(countOnBoard, word, x, y, direction);
	int adjecentWordPoints = 0;
	if (legalPlacement(word, x, y, direction, countOnBoard, adjecentWordPoints))
	{
		std::pair<int, int> tile;
		for (int i = 0; i < word.length(); i++)
		{
			if (direction == "DOWN")
				tile = std::make_pair(y - 1 + i, x - 1);
			else
				tile = std::make_pair(y - 1, x - 1 + i);
			if (ScrabbleB.getLetter(tile.second, tile.first) == ' ') {
				std::string isBlank = "N";
				std::cout << "Is letter " << word[i] << " supposed to be a blank tile? (Y/N)" << std::endl;
				std::cin >> isBlank;
				if (isBlank == "Y")
				{
					ScrabbleLetters currentLetter(word[i], 0);
					ScrabbleB.setLetter(currentLetter, tile.first, tile.second);
				}
				else {
					ScrabbleLetters currentLetter(word[i]);
					ScrabbleB.setLetter(currentLetter, tile.first, tile.second);
				}
			}

		}
	}
}


void Game::countWordLetters(int* countWord, std::string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		countWord[int(word[i]) - 65]++;
	}
}

void Game::countPlayerLetters(int* countPlayer, int & countBlanks)
{
	for (int i = 0; i < 7; i++)
	{
		if (PlayersLetters[i].getLetter() != '.' && PlayersLetters[i].getLetter() != '*')
		{
			countPlayer[int(PlayersLetters[i].getLetter()) - 65]++;
		}
		else if (PlayersLetters[i].getLetter() == '*')
		{
			countBlanks++;
		}
	}
}

void Game::countBoardLetters(int* countOnBoard, std::string word, int x, int y ,std::string direction)
{
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

void Game::giveBestWord()
{
	std::string filename = "./Words/English/words.txt";
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string word;
		int progress = 0;
		int total = 279496;
		int completion = 0;
		while (std::getline(file, word))
		{
			for (int i = 0; i < 14; i++)
			{
				int x = i+1;
				for (int j = 0; j < 14; j++)
				{
					int y = j+1;
					for (int m = 0; m < 2; m++)
					{
						std::string direction = m == 0 ? "DOWN" : "RIGHT";

						if (ScrabbleB.getLetter(i, j) != ' ' || (i==7 && j==7)) {
							int countWord[alphabetLength] = { 0 };
							int countOnBoard[alphabetLength] = { 0 };
							int countPlayer[alphabetLength] = { 0 };
							int countBlanks = 0;
							countLetters(countWord, countOnBoard, countPlayer, word, x, y, direction, countBlanks);
							int missing = missingLetters(countWord, countOnBoard, countPlayer, countBlanks);
							int adjecentWordPoints = 0;
							if (missing == 0 && legalPlacement(word, x, y, direction, countOnBoard, adjecentWordPoints))
							{
								std::cout << word << " at [" << x << "],[" << y << "] " << direction << "WARDS" << std::endl;
							}
						}
					}
				}
			}
			/*
			progress++;
			completion = progress * 100 / total;
			std::cout << "\r";
			std::cout << "[";
			for (int j = 0; j < completion / 10; j++)
			{
				std::cout << (char)254u;
			}
			for (int j = 0; j < 10 - (completion / 10); j++)
			{
				std::cout << "-";
			}
			*/
			/*
			progress++;
			if (completion != progress * 100 / total) 
			{
				std::cout << completion << "%" << std::endl;
				completion = progress * 100 / total;
			}
			*/
		}
		std::cout << "Those are all the words you could place " << std::endl;
		system("PAUSE");
	}
	//file.close();
}

/*
int Game::calculatePoints()
{
		int wordMultiplier = 1;
		for (int i = 0; i < word.length(); i++)
		{
			bool removeFromUser = false;
			int j = 0;
			std::pair<int, int> tile;
			if (direction == "DOWN")
				tile = std::make_pair(y - 1 + i, x - 1);
			else
				tile = std::make_pair(y - 1, x - 1 + i);

			if (ScrabbleB.getLetter(tile.second, tile.first) == ' ')
			{
				int letterPoints = 0;
				while (!removeFromUser && j < 7)
				{
					if (PlayersLetters[j].getLetter() == toupper(word[i]))
					{
						letterPoints = PlayersLetters[j].getPoints();
						int bonusAmount = ScrabbleB.getBonus(tile.second, tile.first);
						if (ScrabbleB.getBonusType(tile.second, tile.first) == 'S')
						{
							wordMultiplier *= bonusAmount;
							currentWordPoints += letterPoints;
						}
						else
						{
							currentWordPoints += letterPoints * bonusAmount;
						}
						ScrabbleLetters Empty('.', 0);
						PlayersLetters[j] = Empty;
						removeFromUser = true;
					}
					j++;
				}
				ScrabbleB.setLetter(ScrabbleLetters(word[i], letterPoints), tile.first, tile.second);
			}
			else
			{
				currentWordPoints += ScrabbleB.getScrabbleLetter(tile.second, tile.first).getPoints();
			}
		}
		//points += currentWordPoints * wordMultiplier;
		//points += adjecentWordPoints;
}
*/