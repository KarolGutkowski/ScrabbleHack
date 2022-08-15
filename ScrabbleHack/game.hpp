#include "board.hpp"
class Game
{
	friend class Board;
private:
	ScrabbleLetters PlayersLetters[7];
public:
	Game();
	void enterLetters();
	void placeWord();
};