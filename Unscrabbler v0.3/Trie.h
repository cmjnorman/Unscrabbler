#pragma once
#include <map>
#include <string>
#include <vector>
#include "MoveTemplate.h"


class Trie
{
private:
	bool isWordEnd;
	std::map<char, Trie*> letters;
public:
	Trie() : isWordEnd(false) {}
	void insert(std::string);
	bool search(std::string);
	std::vector<std::string> findWordsFromTemplate(std::string availableLetters, std::string currentWord, Trie* currentNode, std::vector<std::string> anagrams, MoveTemplate temp);
};

