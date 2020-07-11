#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include "Tetromino.h"
#include <thread>
class Game {
	COORD topLeft = { 0, 0 };
	int x1, y1, x2, y2, x3, y3, x4, y4;
	enum State {left, right, down, RLeft, RRight};
	//char cmatrix[26][14];
	int score;
	State state;
	Tetromino a;
	TempArray TmpArray;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	bool AllowRefresh = true;

	void clear_screen(char fill = ' ') {
		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;

		GetConsoleScreenBufferInfo(console, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(console, fill, cells, tl, &written);
		FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(console, tl);
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
			Sleep(10);
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
		while (1==1) {
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
					a = Tetromino();
					a.getPos(x1, y1, x2, y2, x3, y3, x4, y4);
				}
				break;
			case 3:
				a.Rotate_Left(TmpArray);
			case 4:
				a.Rotate_Right(TmpArray);
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
public: 
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
				Sleep(54);
				
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
			else if ((GetKeyState('X')) & 0x8000) { // Rotate Right
				state = RRight;
				Sleep(54);
				ChangePosition(x1, y1, x2, y2, x3, y3, x4, y4, state, a);
			}
			
		}
	}
};