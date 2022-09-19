#include <iostream>
#include <iomanip>
#include "board.hpp"
#include <windows.h>


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Board::Board()
{
	std::cout << "Creating the board" << std::endl;
	Bonus S3('S', 3);
	Bonus S2('S', 2);
	Bonus L2('L', 2);
	Bonus L3('L', 3);
	Bonus None(' ' ,1);
	// creating the upper left triangle of the board to be copied later on
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j].first = ScrabbleLetters(' ', 0);
			board[i][j].second = None;
			if (i <= 4) board[i][i].second = S2;
			if (i % 7 == 0 && j % 7 == 0)
			{
				board[i][j].second = S3;
				if(i==7) board[i][j].second = None;
			}
		}
	}
	board[0][3].second = L2;
	board[1][5].second = L3;
	board[2][6].second = L2;
	board[3][7].second = L2;
	board[5][5].second = L3;
	board[6][6].second = L2;
	// end of the upper triangle creation
	
	// copying the left triangle of the board on to the upper left square
	for (int i = 0; i < 8; i++)
	{
		for (int j = i; j < 8; j++)
		{
			board[j][i].second = board[i][j].second;
		}
	}

	// copying upper left square on to entire board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[14-i][j].second = board[i][j].second;
			board[14-i][14-j].second = board[i][j].second;
			board[i][14-j].second = board[i][j].second;
		}
	}
}

void Board::printBoard()
{
	for (int i = 0; i < 16; i++) std::cout << std::setw(3) <<i;
	std::cout << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cout << std::setw(3) << i + 1;
		for (int j = 0; j < 15; j++)
		{
			if(board[i][j].second.getType()=='S') 
				SetConsoleTextAttribute(hConsole, 5*(board[i][j].second.getMultiplier()%3) + 4);
			if (board[i][j].second.getType() == 'L') 
				SetConsoleTextAttribute(hConsole, 5*(board[i][j].second.getMultiplier()%3)+1);
			if (board[i][j].first.getLetter() == ' ')
			{
				std::cout << std::setw(2) << board[i][j].second.getType();
				std::cout << board[i][j].second.getMultiplier();
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 32);
				std::cout << std::setw(3) << board[i][j].first.getLetter();
				//std::cout << board[i][j].first.getPoints();
			}
			SetConsoleTextAttribute(hConsole, 15);
		}
		std::cout << std::endl;
	}
}
void Board::setLetter(ScrabbleLetters L, int x, int y)
{	
	if (board[x][y].first.getLetter() == ' ')
	{
		board[x][y].first = L;
	}
	else
	{
		//std::cout << "Tile [" << x + 1 << "][" << y + 1 << "] is already taken." << std::endl;
		//system("PAUSE");
	}
}

char Board::getLetter(int x, int y)
{
	return board[y][x].first.getLetter();
}