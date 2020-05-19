#pragma once
#include <string>
#include "Direction.h"

struct Move
{
	int x;
	int y;
	Direction direction;
	std::string word;
	int value;
};