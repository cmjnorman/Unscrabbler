#include "Square.h"

void Square::setMultiplier(std::string type, int mult)
{
	if (type == "word")
	{
		wordMultiplier = mult;
	}
	else if (type == "letter")
	{
		letterMultiplier = mult;
	}
}

std::string Square::letterForPrint() const
{
	std::string out = " ";
	out += letter;
	out += " ";
	return out;
}

std::string Square::getGhost() const
{
	std::string out;
	if (ghost)
	{
		out = "(";
		out += letter;
		out += ")";
		return out;
	}
	out += letter;
	return out;
}