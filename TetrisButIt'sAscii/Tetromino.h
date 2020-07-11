#pragma once
#include <random>
class TempArray {
public:
	char PubMat[26][14];
};

class Tetromino {
	int startint;
	int type;
	int Block[4][2];

	

	void RandomiseBlock() {
		type = rand() % 7;
		switch (type) {
		case 0: //"longboi"
			for (int x = 0; x < 4; x++) {
				Block[x][0] = 4 + x;
				Block[x][1] = 21;
			}
			break;
		case 1: //L piece Left
			Block[0][0] = 4; Block[0][1] = 22;//High boi
			for (int x = 1; x < 4; x++) {
				Block[x][0] = 3 + x;
				Block[x][1] = 21;
			}
			break;
		case 2: //L piece Right
			Block[3][0] = 5; Block[3][1] = 22;//High boi
			for (int x = 0; x < 3; x++) {
				Block[x][0] = 3 + x;
				Block[x][1] = 21;
			}
			break;
		case 3: // CEWB
			Block[0][0] = 5; Block[0][1] = 21;
			Block[1][0] = 5; Block[1][1] = 22;
			Block[2][0] = 6; Block[2][1] = 21;
			Block[3][0] = 6; Block[3][1] = 22;
			break;
		case 4: //Squiggly right
			Block[0][0] = 4; Block[0][1] = 21;
			Block[1][0] = 5; Block[1][1] = 21;
			Block[2][0] = 5; Block[2][1] = 22;
			Block[3][0] = 6; Block[3][1] = 22;
			break;
		case 5: //Squiggly left
			Block[0][0] = 4; Block[0][1] = 22;
			Block[1][0] = 5; Block[1][1] = 22;
			Block[2][0] = 5; Block[2][1] = 21;
			Block[3][0] = 6; Block[3][1] = 21;
			break;
		case 6: //T ass
			Block[0][0] = 4; Block[0][1] = 21;
			Block[1][0] = 5; Block[1][1] = 21;
			Block[2][0] = 6; Block[2][1] = 21;
			Block[3][0] = 5; Block[3][1] = 22;
		}
	}
public:
	Tetromino() {
		startint = 21;
		RandomiseBlock();
	}
	void setPos(int y1, int y2, int y3, int y4) {
		Block[0][1] = y1;
		Block[1][1] = y2;
		Block[2][1] = y3;
		Block[3][1] = y4;
	}
	void getPos(int &x1, int &y1, int &x2,int &y2,int &x3,int &y3,int &x4,int &y4) {
		x1 = Block[0][0]; y1 = Block[0][1];
		x2 = Block[1][0]; y2 = Block[1][1];
		x3 = Block[2][0]; y3 = Block[2][1];
		x4 = Block[3][0]; y4 = Block[3][1];
	}
	void Left(TempArray Temp) {
		int c = 0;
		for (int i = 0; i < 4; i++) {
			if (Block[i][0] == 1) {
				c++;
			}
		}
		for (unsigned i = 0; i < 4; i++) {
			if (Temp.PubMat[Block[i][1]][Block[i][0]-1] == '#') {
				int g = 0;
				for (unsigned j = 0; j < 4; j++) {
					if ((Block[i][0]-1) == Block[j][0] && (Block[i][1]) == Block[j][1]) {
						g++;
					}
				}
				if (g == 0) {
					c++;
				}
			}
		}
		if (c == 0) {
			for (int i = 0; i < 4; i++) {
				Block[i][0]--;
			}
		}
	}
	void Right(TempArray Temp) {
		int c = 0;
		for (int i = 0; i < 4; i++) {
			if (Block[i][0] == 10) {
				c++;
			}
		}
		for (unsigned i = 0; i < 4; i++) {
			if (Temp.PubMat[Block[i][1]][Block[i][0] + 1] == '#') {
				int g = 0;
				for (unsigned j = 0; j < 4; j++) {
					if ((Block[i][0] + 1) == Block[j][0] && (Block[i][1]) == Block[j][1]) {
						g++;
					}
				}
				if (g == 0) {
					c++;
				}
			}
		}
		if (c == 0) {
			for (int i = 0; i < 4; i++) {
				Block[i][0]++;
			}
		}	
	}
	void Down() {
		int c = 0;
		for (int i = 0; i < 4; i++) {
			if (Block[i][1] == 0) {
				c++;
			}
		}
		if (c == 0) {
			for (int i = 0; i < 4; i++) {
				Block[i][1]--;
			}
		}
	}
	bool CanIFall(TempArray Temp) {
		for (unsigned i = 0; i < 4; i++) {
			if (Temp.PubMat[Block[i][1] - 1][Block[i][0]] == '#') {
				int c = 0;
				for (unsigned j = 0; j < 4; j++) {
					if (Block[i][0] == Block[j][0] && (Block[i][1]-1) == Block[j][1]) {
						c++;
					}
				}
				if (c == 0) {
					return false;
				}
			}
		}
		for (unsigned i = 0; i < 4; i++) {
			if ((Block[i][1]-1)<0) {
				return false;
			}
		}
		return true;
	}
	void Rotate_Left(TempArray Temp) {
		char Array[6][6];
		int TempBlock[4][2];
		int Xsub = Block[0][0] - 3, Ysub = Block[0][1] - 3;
		for (unsigned i = 0; i < 4; i++) {
			Array[Block[i][0] - Xsub][Block[i][1] - Ysub] = '#';
		}
		for (int x = 0; x < 3; x++) { 
			for (int y = x; y < 5 - x; y++) {			
				int temp = Array[x][y];
				Array[x][y] = Array[y][5 - x];
				Array[y][5 - x] = Array[5 - x][5 - y];
				Array[5 - x][5 - y] = Array[5 - y][x];
				Array[5 - y][x] = temp;
			}
		}
		for (unsigned i = 0, temp = 0; i < 6; i++) {
			for (unsigned j = 0; j < 6; j++) {
				if (Array[i][j] == '#') {
					TempBlock[temp][0] = i;
					TempBlock[temp][1] = j;
					temp++;
				}
			}
		}
		Xsub = Block[2][0] - TempBlock[2][0];
		Ysub = Block[2][1] - TempBlock[2][1];
		bool CancelCulture = false;
		for (unsigned i = 0; i < 4; i++) {
			int glob = 0;
			for (unsigned j = 0; j < 4; j++) {
				if (Temp.PubMat[TempBlock[i][1] + Ysub][TempBlock[i][0] + Xsub] == '#') {
					if ((Block[j][0] == (TempBlock[i][0] + Xsub) && Block[j][1] == (TempBlock[i][1] + Ysub))) {
						glob++;
					}
				}
				else if (Temp.PubMat[TempBlock[i][1] + Ysub][TempBlock[i][0] + Xsub] == '/') { glob++; }
			}
			if (glob == 0) { CancelCulture = true; }
		}
		if (CancelCulture == false) {
			for (unsigned i = 0; i < 4; i++) {
				Block[i][0] = TempBlock[i][0] + Xsub;
				Block[i][1] = TempBlock[i][1] + Ysub;
			}
		}
	}
	void Rotate_Right(TempArray Temp) {
		for (unsigned i = 0; i < 3; i++) { Rotate_Left(Temp); }
	}
};