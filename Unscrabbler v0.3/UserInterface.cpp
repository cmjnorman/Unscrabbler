#include "UserInterface.h"
#include "Dictionary.h"
#include "Board.h"
#include "Direction.h"
#include "Player.h"
#include <typeinfo>

using std::cin;
using std::cout;
using std::endl;

void UserInterface::run()
{
	cout << endl << "Welcome to my Scrabble Descrabbler!" << endl << endl;
	cout << "First we will need to program in the board to match your pysical board." << endl;

	std::string hand;
	std::string input;
	Board b;

	cout << "Current Board:" << endl;
	b.printBoard();

	while (true) {
		cout << "Do you want to add a word to the board? (y/n)" << endl;
		cin >> input;
		if (input == "y")
		{
			int x;
			int y;
			Direction d;
			std::string word;

			while (true) {
				cout << "Enter x coordinate of word. (0 - 14, left to right)" << endl;
				cin >> input;
				if (stoi(input) >= 0 && stoi(input) < 15)
				{
					x = stoi(input);
					break;
				}
				cout << "Not a valid selection!" << endl;
			}
			while (true)
			{
				cout << "Enter y coordinate of word. (0 - 14, top to bottom)" << endl;
				cin >> input;
				if (stoi(input) >= 0 && stoi(input) < 15)
				{
					y = stoi(input);
					break;
				}
				cout << "Not a valid selection!" << endl;
			}

			while (true)
			{
				cout << "Enter word direction. (horizontal or vertical (h/v))" << endl;
				cin >> input;
				if (input == "horizontal" || input == "h")
				{
					d = Direction::RIGHT;
					break;
				}
				if (input == "vertical" || input == "v")
				{
					d = Direction::DOWN;
					break;
				}
				cout << "Not a valid selection!" << endl;
			}

			cout << "Enter word." << endl;
			cin >> word;

			b.addWord(x, y, d, word);
			b.printBoard();
		}
		if (input == "n")
		{
			break;
		}
	}
	cout << endl << "Great! Now please enter the 7 letters in your hand." << endl;
	while (true)
	{
		cin >> input;
		if (input.length() == 7)
		{
			hand = input;
			break;
		}
		cout << "Not a valid selection! You must enter a 7 letter string." << endl;
	}

	Dictionary d;

	Player p(hand);

	cout << "Calculating best move!" << endl;

	std::vector<Move> moves = p.getMoves(b, d.getTrie());

	cout << "Done!" << endl;

	cout << endl << "Your best move is: " << endl << endl;
	for (Move move : moves)
	{
		p.showMove(b, move);
		cout << endl << "Would you like to use this move? y/n" << endl;
		cin >> input;
		if (input == "y") b.addWord(move.x, move.y, move.direction, move.word); break;
	}

	b.printBoard();
}
