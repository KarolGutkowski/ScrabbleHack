#include "letters.hpp"
#include <utility>
class Bonus
{
private:
	char type;
	int multiplier;
public:
	Bonus() :type(NULL), multiplier(0) {}
	Bonus(char type, int multiplier) :type(type), multiplier(multiplier) {}
	char getType() { return type; }
	int getMultiplier() { return multiplier; }
};

class Board
{
friend class ScrabbleLetters;
friend class Bonus;
private:
	std::pair<ScrabbleLetters,Bonus> board[15][15];
public:
	Board();
	char getLetter(int x, int y);
	void setLetter(ScrabbleLetters L,int x,int y);
	void printBoard();
};
