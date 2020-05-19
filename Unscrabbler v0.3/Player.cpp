#include "Player.h"
#include <iostream>
#include <algorithm>

bool Player::wordAllowed(Board b, std::string const& word, MoveTemplate const& temp, Trie* t) const
{
    b.addWord(temp.x, temp.y, temp.direction, word);
    int x = temp.x;
    int y = temp.y;
    for (int l = 0; l < word.length(); l++)
    {
        std::vector<std::string> v = b.createdWords(x, y);
        for (std::string s : v)
        {
            if (!t->search(s)) return false;
        }
        switch (temp.direction)
        {
        case(Direction::RIGHT):
            x++;
            break;
        case(Direction::DOWN):
            y++;
            break;
        }
    }
    return true;
}

std::vector<MoveTemplate> Player::getMoveTemplates(Board b) const
{
    std::vector<MoveTemplate> templates;
    std::vector<std::vector<Square>> board = b.getBoard();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
            std::map<char, int> existingCharacters;
            int minLength = 0;
            int maxLength = 0;
            int wordLength = 7;
            for (int l = 0; l < wordLength; l++)
            {
                if (b.adjacentIsOccupied(j + l, i)) 
                {
                    if (minLength == 0) minLength = l + 1;
                    if (board[i][j + l].isOccupied())
                    {
                        existingCharacters.insert(std::make_pair(board[i][j + l].getLetter(), l));
                        wordLength++;
                    }
                }
                if (l == wordLength - 1 || j + l == 14)
                {
                    maxLength = l + 1;
                    if (minLength != 0) templates.push_back({ j, i, minLength, maxLength, Direction::RIGHT, existingCharacters });
                    break;
                }
            }
		}
	}
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            std::map<char, int> existingCharacters;
            int minLength = 0;
            int maxLength = 0;
            int wordLength = 7;
            for (int l = 0; l < wordLength; l++)
            {
                if (b.adjacentIsOccupied(j, i + l))
                {
                    if (minLength == 0) minLength = l + 1;
                    if (board[i + l][j].isOccupied())
                    {
                        existingCharacters.insert(std::make_pair(board[i + l][j].getLetter(), l));
                        wordLength++;
                    }
                }
                if (l == wordLength - 1 || i + l == 14)
                {
                    maxLength = l + 1;
                    if (minLength != 0) templates.push_back({ j, i, minLength, maxLength, Direction::DOWN, existingCharacters });
                    break;
                }
            }
        }
    }
    return templates;
}

std::vector<Move> Player::getMoves(Board const& b, Trie* t) const
{
    std::vector<MoveTemplate> templates = getMoveTemplates(b);
    std::vector <Move> moves;
    for (MoveTemplate temp : templates)
    {
        std::vector <std::string> words;
        words = t->findWordsFromTemplate(hand, "", t, words, temp);
        for (std::string word : words)
        {
            Move move = { temp.x, temp.y, temp.direction, word };
            int value = b.moveValue(move);
            move.value = value;
            if (wordAllowed(b, word, temp, t)) moves.push_back(move);
        }
    }
    
    std::sort(moves.begin(), moves.end(), [this](Move m1, Move m2) { return m1.value > m2.value; });
    return moves;
}

void Player::showMove(Board b, Move const& move)
{
    b.addWord(move.x, move.y, move.direction, move.word, true);
    b.printBoard();
}

