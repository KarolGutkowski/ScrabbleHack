#include <iostream>
#include <utility>



class ScrabbleLetters
{
private:
	wchar_t letter;
	int points;
	static constexpr std::pair<char, int> lettersPoints[28] = {
		std::make_pair('*',0),
		std::make_pair('A',1),
		std::make_pair('E',1),
		std::make_pair('I',1),
		std::make_pair('L',1),
		std::make_pair('N',1),
		std::make_pair('O',1),
		std::make_pair('R',1),
		std::make_pair('S',1),
		std::make_pair('T',1),
		std::make_pair('U',1),
		std::make_pair('D',2),
		std::make_pair('G',2),
		std::make_pair('D',2),
		std::make_pair('B',3),
		std::make_pair('C',3),
		std::make_pair('M',3),
		std::make_pair('P',3),
		std::make_pair('F',4),
		std::make_pair('H',4),
		std::make_pair('V',4),
		std::make_pair('W',4),
		std::make_pair('Y',4),
		std::make_pair('K',5),
		std::make_pair('J',8),
		std::make_pair('X',8),
		std::make_pair('Q',10),
		std::make_pair('Z',10)
	};
public:
	ScrabbleLetters();
	ScrabbleLetters(char letter, int points);
	char getLetter();
	int getPoints();
	friend std::ostream& operator<<(std::ostream& out, ScrabbleLetters L);
	friend std::istream& operator>>(std::istream& in, ScrabbleLetters& L);
};