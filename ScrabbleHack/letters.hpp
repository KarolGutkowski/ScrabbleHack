#include <iostream>
class ScrabbleLetters
{
private:
	wchar_t letter;
	int points;
public:
	ScrabbleLetters();
	ScrabbleLetters(wchar_t letter, int points);
	wchar_t getLetter();
	friend std::wostream& operator<<(std::wostream& out, ScrabbleLetters L);
	friend std::wistream& operator>>(std::wistream& in, ScrabbleLetters& L);
};