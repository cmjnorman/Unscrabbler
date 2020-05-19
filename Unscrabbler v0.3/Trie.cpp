#include "Trie.h"

void Trie::insert(std::string word)
{
	Trie* currentNode = this;
	for (size_t i = 0; i < word.length(); i++)
	{
		char currentLetter = word[i];
		if (currentNode->letters.find(currentLetter) == currentNode->letters.end())
		{
			currentNode->letters.insert(std::make_pair(currentLetter, new Trie()));
		}
		currentNode = currentNode->letters[currentLetter];
	}
	currentNode->isWordEnd = true;
}

bool Trie::search(std::string word) 
{
	Trie* currentNode = this;
	for (size_t i = 0; i < word.length(); i++)
	{
		if (currentNode->letters.find(word[i]) != currentNode->letters.end())
		{
			currentNode = currentNode->letters[word[i]];
		}
		else return false;
	}
	return currentNode->isWordEnd;
}

std::vector<std::string> Trie::findWordsFromTemplate(std::string availableLetters, std::string currentWord, Trie* currentNode, std::vector<std::string> anagrams, MoveTemplate temp)
{
	if (currentNode->isWordEnd)
	{
		if (std::find(anagrams.begin(), anagrams.end(), currentWord) == anagrams.end())
		{
			if (currentWord.length() >= temp.minLength && currentWord.length() <= temp.maxLength) anagrams.push_back(currentWord);
		}

	}

	for (size_t i = 0; i < availableLetters.length(); i++)
	{
		for (std::map<char, int>::iterator iter = temp.existingCharacters.begin(); iter != temp.existingCharacters.end(); iter++)
		{
			if (currentWord.length() == iter->second)
			{
				if (currentNode->letters.find(iter->first) != currentNode->letters.end())
				{
					anagrams = findWordsFromTemplate(availableLetters, currentWord + iter->first, currentNode->letters[iter->first], anagrams, temp);
				}
				return anagrams;
			}
		}
		if (currentNode->letters.find(availableLetters[i]) != currentNode->letters.end())
		{
			std::string newLetters = availableLetters;
			newLetters.erase(i, 1);

			anagrams = findWordsFromTemplate(newLetters, currentWord + availableLetters[i], currentNode->letters[availableLetters[i]], anagrams, temp);
		}
	}

	return anagrams;
}