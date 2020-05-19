#pragma once
#include "Direction.h"
#include <map>

struct MoveTemplate
{
	int x;
	int y;
	int minLength;
	int maxLength;
	Direction direction;
	std::map<char, int> existingCharacters;
};