#include "Dictionary.h"

Dictionary::Dictionary() : wordTrie(new Trie()), words("words.txt")
{
	std::cout << "Creating word trie..." << std::endl;
	std::string word;
	while (getline(words, word))
	{
		wordTrie->insert(word);
	}
	std::cout << "Done." << std::endl;
}

Trie* Dictionary::getTrie() const
{
	return wordTrie;
}
