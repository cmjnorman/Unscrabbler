#pragma once
#include <string>

class Square
{
private:
	char letter;
	bool ghost;
public:
	int letterMultiplier;
	int wordMultiplier;
	Square() : letter(' '), ghost(false), letterMultiplier(1), wordMultiplier(1) {}
	void setLetter(char c, bool isGhost = false) { letter = c; ghost = isGhost; }
	bool isGhost() const { return ghost; }
	void setGhostLetter(char c) { letter = c; ghost = true; }
	char getLetter() const { return letter; }
	std::string getGhost() const;
	void setMultiplier(std::string type, int mult);
	bool isOccupied() const { return letter != ' '; }
	std::string letterForPrint() const;
};

