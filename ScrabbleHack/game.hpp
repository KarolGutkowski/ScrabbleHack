#include "board.hpp"
class Game
{
	friend class Board;
private:
	ScrabbleLetters PlayersLetters[7];
	int points;
public:
	Board ScrabbleB;
	Game();
	void enterLetters();
	void placeWord();
	bool IsLegalWord(std::string&);
	void enterData(std::string &word, int &x, int &y, std::string &direction);
	void countLetters(int* countWord, int* countOnBoard, int* countPlayer,
		std::string word, int x, int y, std::string direction, int& countBlanks);
	void countWordLetters(int* countWord,std::string word);
	void countPlayerLetters(int* countPlayer,int& countBlanks);
	void countBoardLetters(int* countOnBoard, std::string word, int x, int y, std::string direction);
	int missingLetters(int* countWord, int* countOnBoard, int* countPlayer, int countBlanks);
	void sortPlayerLetters();
	bool legalPlacement(std::string& word, int& x, int& y, std::string &direction, int* countOnBoard,int& adjecentWordPoints);
	void otherPlayerWord();
	void giveBestWord();
	int calculatePoints(std::string word, std::string direction, int x, int y);
	bool isConnected(std::string word, std::string direction, int x,int y);
};