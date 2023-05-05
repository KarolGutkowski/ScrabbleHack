#include "board.hpp"
#include <vector>
#include <set>
class Game
{
	friend class Board;
private:
	ScrabbleLetters PlayersLetters[7];
	std::vector<std::string> wordsList;
	std::set<std::string> wordsSet;
	int points;
public:
	Board ScrabbleB;
	Game();
	void Start();
	void loadData();
	void showCurrentGameMenu();
	void enterLetters();
	void placeWord();
	bool IsLegalWord(std::string&);
	void enterData(std::string &word, int &x, int &y, std::string &direction);
	void countLetters(std::vector<int>& countWord, std::vector<int>& countOnBoard, std::vector<int>& countPlayer,
		std::string word, int x, int y, std::string direction, int& countBlanks);
	void countWordLetters(std::vector<int>& countWord,std::string word);
	void countPlayerLetters(std::vector<int>& countPlayer, int& countBlanks);
	void countBoardLetters(std::vector<int>& countOnBoard, std::string word, int x, int y, std::string direction);
	int missingLetters(std::vector<int>& countWord, std::vector<int>& countOnBoard, std::vector<int>& countPlayer, int countBlanks);
	void sortPlayerLetters();
	bool legalPlacement(std::string& word, int& x, int& y, std::string &direction, std::vector<int>& countOnBoard,int& adjecentWordPoints);
	void otherPlayerWord();
	void giveBestWord();
	int calculatePoints(std::string word, std::string direction, int x, int y);
	bool isConnected(std::string word, std::string direction, int x,int y);
};