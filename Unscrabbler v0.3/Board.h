#pragma once

#include <string>
#include <vector>
#include "Direction.h"
#include "Square.h"
#include "MoveTemplate.h"
#include "Move.h"
#include "Trie.h"

class Board
{
private:
	std::vector<std::vector<Square>> squares;
public:
	Board();
	std::vector<std::vector<Square>> getBoard() { return squares; }
	void addWord(int x, int y, Direction direction, std::string word, bool ghost = false);
	void printBoard() const;
	bool adjacentIsOccupied(int x, int y) const;
	std::vector<std::string> createdWords(int x, int y) const;
	int letterValue(int x, int y, char letter) const;
	int moveValue(Move const& move) const;
};
