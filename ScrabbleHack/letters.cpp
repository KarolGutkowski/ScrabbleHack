#include "letters.hpp"
#include <iostream>

ScrabbleLetters::ScrabbleLetters(char letter, int points) :letter(letter),points(points) {}
ScrabbleLetters::ScrabbleLetters() : letter(' '), points(1) {}
std::ostream& operator<<(std::ostream& out, ScrabbleLetters L)
{
	out << L.letter << "(" << L.points << ")";
	return out;
}

char ScrabbleLetters::getLetter()
{
	return letter;
}

std::istream& operator>>(std::istream& in, ScrabbleLetters& L)
{
	std::cout << "Letter: ";
	in >> L.letter;
	std::cout << std::endl;
	std::cout << "Point: ";
	in >> L.points;
	std::cout << std::endl;
	return in;
}