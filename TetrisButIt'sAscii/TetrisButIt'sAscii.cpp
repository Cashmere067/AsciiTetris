// TetrisButIt'sAscii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "rlutil.h";
#include "Game.h";
using namespace std;

int main() {
	cout << "-------------------------------\n";
	cout << "Welcome to Ascii Tetris\n\n";
	system("pause");

	//Change font so tetris is easier to see
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	//end of change font
	Game NewGame = Game();
	NewGame.startgame();
	//add timer thing
	return 0;
	//add moving
}

