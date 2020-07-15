#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include "Tetromino.h"
#include <thread>
#include <list>
class Game {
	std::thread Threadobj;
	COORD topLeft = { 0, 0 };
	int x1, y1, x2, y2, x3, y3, x4, y4;
	enum State { left, right, down, RLeft, RRight };
	//char cmatrix[26][14];
	int score;
	State state;
	Tetromino a;
	TempArray TmpArray;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	bool AllowRefresh = true;
	bool GameOver = false;

	
	void CheckFullLines() {
		std::list<int> BoppedLines;
		int i = 0;
		for (unsigned x = 0; x < 22; x++) {
			int count = 0;
			for (unsigned y = 1; y < 11; y++) {
				if (TmpArray.PubMat[x][y] == '#') { count++; }
			}
			if (count == 10) { BoppedLines.push_back(x); i++; }
		}
		if (i > 0) {
			switch (i) {
			case 1:
				score += 40;
				break;
			case 2:
				score += 100;
				break;
			case 3:
				score += 300;
				break;
			case 4:
				score += 1200;
				break;
			}
			int TempVal = BoppedLines.front();
			for (unsigned potato = 0; potato < BoppedLines.size(); potato++) { for (unsigned Beet = 1; Beet < 11; Beet++) { TmpArray.PubMat[BoppedLines.front()][Beet] = '/'; } BoppedLines.pop_front(); }
			for (unsigned cactus = TempVal + i; cactus < 22; cactus++) { for (unsigned banana = 1; banana < 11; banana++) { TmpArray.PubMat[int(cactus) - i][banana] = TmpArray.PubMat[cactus][banana]; } }
			//pseudocodearea below
			//Get How Many Are Cleared (that would be i)
			//then shift all the blocks above where those two are missing by how many where down there

		}
	}
	void prepPlayField() {
		for (int x = 0; x < 26; x++) {
			for (int y = 0; y < 12; y++) {
				TmpArray.PubMat[x][y] = '/';
			}
		}
		for (int x = 0; x < 26; x++) {
			TmpArray.PubMat[x][12] = '\0';
			TmpArray.PubMat[x][0] = '[';
			TmpArray.PubMat[x][11] = ']';
		}
	}

	void tetrominoDisplayer() {
		//clear_screen();
		if (AllowRefresh == false) {
			while (AllowRefresh != true) {}
		}
		AllowRefresh = false;
		SetConsoleCursorPosition(console, topLeft);
		for (int x = 21; x >= 0; x--) {
			printf("%s", TmpArray.PubMat[x]);
			printf("\n");
		}
		std::cout << "\n\nScore: " + std::to_string(score);
		printf("\n");
		AllowRefresh = true;
	}

	void threadFn() { //This is simply responsible for moving the tetrominoes down
		while (1 == 1) {
			if (GameOver) {
				Threadobj.~thread();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000000000));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1250));
			state = down;
			ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
		}
	}
	void ChangePosition(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3, int& x4, int& y4, int Direction, Tetromino& a) {
		switch (Direction) {
		case 0:
			a.Left(TmpArray);
			break;
		case 1:
			a.Right(TmpArray);
			break;
		case 2: //setpos shit
			if (a.CanIFall(TmpArray) == true) {
				a.Down();
			}
			else {
				if (y1 > 21 || y2 > 21 || y3 > 21 || y4 > 21) { 
					GamOver();
				}
				CheckFullLines();
				a = Tetromino();
				a.getPos(x1, y1, x2, y2, x3, y3, x4, y4);
			}
			break;
		case 3:
			if (a.Check_Left(TmpArray) == true) {
				a.Rotate_Left(TmpArray);
			}
			break;
		case 4:
			if (a.Check_Right(TmpArray) == true) {
				a.Rotate_Right(TmpArray);
			}
			break;
		}
		TmpArray.PubMat[y1][x1] = '/';
		TmpArray.PubMat[y2][x2] = '/';
		TmpArray.PubMat[y3][x3] = '/';
		TmpArray.PubMat[y4][x4] = '/';
		a.getPos(x1, y1, x2, y2, x3, y3, x4, y4);
		TmpArray.PubMat[y1][x1] = '#';
		TmpArray.PubMat[y2][x2] = '#';
		TmpArray.PubMat[y3][x3] = '#';
		TmpArray.PubMat[y4][x4] = '#';
		tetrominoDisplayer();
		
	}
	void GamOver() {
		GameOver = true;
		Sleep(200);
		clear_screen();
		std::cout << "Better Luck next time!\n Press any key to continue...";
		clear_screen();
		clear_screen();
		clear_screen();
		clear_screen();

		std::cout << "Better Luck next time!\n The Program Will Now Exit...";
		Sleep(5000);
		exit(0);
	
	}
public:
	void clear_screen(char fill = ' ') {
		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;

		GetConsoleScreenBufferInfo(console, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(console, fill, cells, tl, &written);
		FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(console, tl);
	}
	
	Game() {
		prepPlayField();
		score = 0;
	}
	void startgame() {
		a.getPos(x1, y1, x2, y2, x3, y3, x4, y4);
		TmpArray.PubMat[y1][x1] = '#';
		TmpArray.PubMat[y2][x2] = '#';
		TmpArray.PubMat[y3][x3] = '#';
		TmpArray.PubMat[y4][x4] = '#';
		clear_screen();
		tetrominoDisplayer();
		std::thread Threadobj([&] { threadFn(); }); //close thread after user dies.
		while (1 == 1) {
			if (GetKeyState(VK_LEFT) & 0x8000) {
				state = left;
				Sleep(56);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
			else if ((GetKeyState(VK_RIGHT)) & 0x8000) {
				state = right;
				Sleep(56);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);

			}
			else if ((GetKeyState(VK_DOWN)) & 0x8000) {
				state = down;
				Sleep(56);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
			else if ((GetKeyState('Z')) & 0x8000) { // Rotate Left
				state = RLeft;
				Sleep(65);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
			else if ((GetKeyState('X')) & 0x8000) { // Rotate Right
				state = RRight;
				Sleep(65);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
		}

	}
};