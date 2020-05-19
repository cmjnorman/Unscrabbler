#include "Board.h"
#include <iostream>

Board::Board() : squares(15, std::vector<Square>(15, Square()))
{
	squares[0][0].setMultiplier("word", 3);
	squares[0][7].setMultiplier("word", 3);
	squares[0][14].setMultiplier("word", 3);
	squares[7][0].setMultiplier("word", 3);
	squares[7][14].setMultiplier("word", 3);
	squares[14][0].setMultiplier("word", 3);
	squares[14][7].setMultiplier("word", 3);
	squares[14][14].setMultiplier("word", 3);

	squares[1][1].setMultiplier("word", 2);
	squares[1][13].setMultiplier("word", 2);
	squares[2][2].setMultiplier("word", 2);
	squares[2][12].setMultiplier("word", 2);
	squares[3][3].setMultiplier("word", 2);
	squares[3][11].setMultiplier("word", 2);
	squares[4][4].setMultiplier("word", 2);
	squares[4][10].setMultiplier("word", 2);
	squares[7][7].setMultiplier("word", 2);
	squares[10][4].setMultiplier("word", 2);
	squares[10][10].setMultiplier("word", 2);
	squares[11][3].setMultiplier("word", 2);
	squares[11][11].setMultiplier("word", 2);
	squares[12][2].setMultiplier("word", 2);
	squares[12][12].setMultiplier("word", 2);
	squares[13][1].setMultiplier("word", 2);
	squares[13][13].setMultiplier("word", 2);

	squares[1][5].setMultiplier("letter", 3);
	squares[1][9].setMultiplier("letter", 3);
	squares[5][1].setMultiplier("letter", 3); 
	squares[5][5].setMultiplier("letter", 3);
	squares[5][9].setMultiplier("letter", 3);
	squares[5][13].setMultiplier("letter", 3);
	squares[9][1].setMultiplier("letter", 3);
	squares[9][5].setMultiplier("letter", 3);
	squares[9][9].setMultiplier("letter", 3);
	squares[9][14].setMultiplier("letter", 3);
	squares[13][5].setMultiplier("letter", 3);
	squares[13][9].setMultiplier("letter", 3);
		
	squares[0][3].setMultiplier("letter", 2);
	squares[0][11].setMultiplier("letter", 2);
	squares[2][6].setMultiplier("letter", 2);
	squares[2][8].setMultiplier("letter", 2);
	squares[3][0].setMultiplier("letter", 2);
	squares[3][7].setMultiplier("letter", 2);
	squares[3][14].setMultiplier("letter", 2);
	squares[6][2].setMultiplier("letter", 2);
	squares[6][6].setMultiplier("letter", 2);
	squares[6][8].setMultiplier("letter", 2);
	squares[6][12].setMultiplier("letter", 2);
	squares[7][3].setMultiplier("letter", 2);
	squares[7][11].setMultiplier("letter", 2);
	squares[8][2].setMultiplier("letter", 2);
	squares[8][6].setMultiplier("letter", 2);
	squares[8][8].setMultiplier("letter", 2);
	squares[8][12].setMultiplier("letter", 2);
	squares[11][0].setMultiplier("letter", 2);
	squares[11][7].setMultiplier("letter", 2);
	squares[11][14].setMultiplier("letter", 2);
	squares[12][6].setMultiplier("letter", 2);
	squares[12][8].setMultiplier("letter", 2);
	squares[14][3].setMultiplier("letter", 2);
	squares[14][11].setMultiplier("letter", 2);
}

void Board::addWord(int x, int y, Direction direction, std::string word, bool ghost)
{
	bool spaceAvailable = true;
	for (size_t i = 0; i < word.length(); i++)
	{
		switch (direction)
		{
		case Direction::RIGHT:
			if(x + i > 14 || squares[y][x + i].isOccupied() && toupper(word[i]) != squares[y][x + i].getLetter()) spaceAvailable = false;
			break;
		case Direction::DOWN:
			if (y + i > 14 || squares[y + i][x].isOccupied() && toupper(word[i]) != squares[y + i][x].getLetter()) spaceAvailable = false;
			break;
		}
	}
	if (spaceAvailable)
	{
		for (size_t i = 0; i < word.length(); i++)
		{
			switch (direction)
			{
			case Direction::RIGHT:
				squares[y][x + i].setLetter(toupper(word[i]), ghost);
				break;
			case Direction::DOWN:
				squares[y + i][x].setLetter(toupper(word[i]), ghost);
				break;
			}
		}
	}
}

void Board::printBoard() const
{
	std::cout << "       0   1   2   3   4   5   6   7   8   9   10  11  12  13  14 " << std::endl 
		<< "     -------------------------------------------------------------" << std::endl
		<< "    |                                                             |" << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cout << " " << i;
		if (i < 10) std::cout << " ";
		std::cout << " | ";
		for (int j = 0; j < 15; j++)
		{
			if (squares[i][j].isGhost())
			{
				std::cout << squares[i][j].getGhost() << ' ';
			}
			else std::cout << squares[i][j].letterForPrint() << ' ';
		}
		std::cout << "|" << std::endl << "    |                                                             |" << std::endl;
	}
	std::cout << "     -------------------------------------------------------------" << std::endl;
}


bool Board::adjacentIsOccupied(int x, int y) const
{
	if (squares[y][x].isOccupied()) return true;
	if (x != 0 && squares[y][x - 1].isOccupied()) return true;
	if (x != 14 && squares[y][x + 1].isOccupied()) return true;
	if (y != 0 && squares[y - 1][x].isOccupied()) return true;
	if (y != 14 && squares[y + 1][x].isOccupied()) return true;
	return false;
}

std::vector<std::string> Board::createdWords(int x, int y) const
{
	std::string leftString;
	std::string rightString;
	std::string upString;
	std::string downString;
	for(int i = 1; i < 15; i++)
	{
		if (x - i > 0 && squares[y][x - i].getLetter() != ' ')
		{
			leftString.insert(leftString.begin(), squares[y][x - i].getLetter());
			continue;
		}
		break;
	}
	for (int i = 1; i < 15; i++)
	{
		if (x + i < 15 && squares[y][x + i].getLetter() != ' ')
		{
			rightString += squares[y][x + i].getLetter();
			continue;
		}
		break;
	}
	for (int i = 1; i < 15; i++)
	{
		if (y - i > 0 && squares[y - i][x].getLetter() != ' ')
		{
			upString.insert(upString.begin(), squares[y - i][x].getLetter());
			continue;
		}
		break;
	}
	for (int i = 1; i < 15; i++)
	{
		if (y + i < 15 && squares[y + i][x].getLetter() != ' ')
		{
			downString += squares[y + i][x].getLetter();
			continue;
		}
		break;
	}
	std::string horizontal = leftString + squares[y][x].getLetter() + rightString;
	std::string vertical = upString + squares[y][x].getLetter() + downString;
	std::vector<std::string> output;
	if (horizontal.length() > 1) output.push_back(horizontal);
	if (vertical.length() > 1) output.push_back(vertical);
	return output;
}

int Board::letterValue(int x, int y, char letter) const
{
	int value = 0;
	switch (letter)
	{
	case '_':
		value = 0;
		break;
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
	case 'L':
	case 'N':
	case 'S':
	case 'T':
	case 'R':
		value = 1;
		break;
	case 'D':
	case 'G':
		value = 2;
		break;
	case 'B':
	case 'C':
	case 'M':
	case 'P':
		value = 3;
		break;
	case 'F':
	case 'H':
	case 'V':
	case 'W':
	case 'Y':
		value = 4;
		break;
	case 'K':
		value = 5;
		break;
	case 'J':
	case 'X':
		value = 8;
		break;
	case 'Q':
	case 'Z':
		value = 10;
	}
	if (!squares[y][x].isOccupied()) value *= squares[y][x].letterMultiplier;
	return value;
}

int Board::moveValue(Move const& move) const
{
	int totalValue = 0;
	int multiplier = 1;
	int ownLettersUsed = 0;
	int x = move.x;
	int y = move.y;
	for (int i = 0; i < move.word.length(); i++)
	{
		totalValue += letterValue(x, y, move.word[i]);
		multiplier *= squares[y][x].wordMultiplier;
		if (!squares[y][x].isOccupied()) ownLettersUsed++;
		if (move.direction == Direction::RIGHT) x++;
		if (move.direction == Direction::DOWN) y++;
	}
	if (ownLettersUsed == 7) totalValue += 50;
	return totalValue * multiplier;
}



