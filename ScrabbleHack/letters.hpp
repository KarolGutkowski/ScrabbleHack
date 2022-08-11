#include <iostream>
class ScrabbleLetters
{
private:
	char letter;
	int points;
public:
	ScrabbleLetters();
	ScrabbleLetters(char letter, int points);
	char getLetter();
	friend std::ostream& operator<<(std::ostream& out, ScrabbleLetters L);
	friend std::istream& operator>>(std::istream& in, ScrabbleLetters& L);
};