#include "letters.hpp"
#include <iostream>
#include <ctype.h>

ScrabbleLetters::ScrabbleLetters(char letter, int points) :letter(letter),points(points) {}
ScrabbleLetters::ScrabbleLetters() : letter(' '), points(1) {}
ScrabbleLetters::ScrabbleLetters(char letter):letter(letter)
{
	letter = toupper(letter);
	for (int i = 0; i < 27; i++)
	{
		if (lettersPoints[i].first == letter)
			points = lettersPoints[i].second;
	}
}
std::ostream& operator<<(std::ostream& out, ScrabbleLetters L)
{
	out << L.letter << "(" << L.points << ")";
	return out;
}

char ScrabbleLetters::getLetter()
{
	return letter;
}

int ScrabbleLetters::getPoints()
{
	return points;
}

std::istream& operator>>(std::istream& in, ScrabbleLetters& L)
{
	std::cout << "Letter: ";
	char letter;
	in >> letter;
	L.letter = toupper(letter);
	for (int i = 0; i < 28; i++)
	{
		if (L.lettersPoints[i].first == L.letter)
			L.points = L.lettersPoints[i].second;
	}
	return in;
}
