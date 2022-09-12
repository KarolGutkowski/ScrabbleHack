#include "letters.hpp"
#include <utility>
class Bonus
{
private:
	wchar_t type;
	int multiplier;
public:
	Bonus() :type(NULL), multiplier(0) {}
	Bonus(wchar_t type, int multiplier) :type(type), multiplier(multiplier) {}
	wchar_t getType() { return type; }
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
	void printBoard();
};
