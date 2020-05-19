#pragma once
#include "Trie.h"
#include <iostream>
#include <fstream>

class Dictionary
{
private:
	Trie* wordTrie;
	std::ifstream words;
public:
	Dictionary();
	Trie* getTrie() const;
};