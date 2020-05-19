#pragma once
#include <vector>
#include "Move.h"
#include "MoveTemplate.h"
#include "Board.h"
#include "Trie.h"

class Player
{
private:
	std::string hand;
public:
	Player(std::string startingHand) : hand(startingHand) {}
	bool wordAllowed(Board b, std::string const& word, MoveTemplate const& temp, Trie* t) const;
	std::vector<MoveTemplate> getMoveTemplates(Board b) const;
	std::vector<Move> getMoves(Board const& b, Trie* t) const;
	void showMove(Board b, Move const& move);
};

