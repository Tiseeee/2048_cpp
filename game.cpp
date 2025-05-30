#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <easyx.h>
#include <Windows.h>
#include <ctime>
#include <random>
using namespace std;

bool Move(int a[4][4]) {
	ExMessage m;
	outtextxy(200, 250, L"press W A S D");
	while (1) {
		peekmessage(&m, EX_KEY);
		if (m.message == WM_KEYDOWN) {
			if (m.vkcode == 'W') {
				for (int i = 0, j = 0, n1 = 0, n2 = 0; i < 4; i++) {
					while (a[j + 1][i] == 0 && j < 3) {
						j++;
						n1 = a[j][i];
					}
					while (a[j + 1][i] == 0 && j < 3) {
						j++;
						n2 = a[j][i];
					}
					if (n1 == n2)
						return true;
					else
						return false;
				}
			}
			if (m.vkcode == 'A') {}
			if (m.vkcode == 'S') {}
			if (m.vkcode == 'D') {}
		}
	}
	return false;
}

bool Move_W(int a[4][4]) {
		bool moved = false;
		for (int col = 0; col < 4; col++) {
			for (int row = 0; row < 3; row++) {
				if (a[row][col] == 0) {
					for (int k = row + 1; k < 4; k++) {
						if (a[k][col] != 0) {
							a[row][col] = a[k][col];
							a[k][col] = 0;
							moved = true;
							break;
						}
					}
				}
			}
			for (int row = 0; row < 3; row++) {
				if (a[row][col] != 0 && a[row][col] == a[row + 1][col]) {
					a[row][col] *= 2;
					a[row + 1][col] = 0;
					moved = true;
					for (int k = row + 1; k < 3; k++) {
						a[k][col] = a[k + 1][col];
					}
					a[3][col] = 0;
				}
			}
		}
		return moved;
	}

void MakeNew24(int a[4][4]) {
	//生成随机数
	random_device rd; 
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 10);
	int b = dis(gen);
	if (b < 8) {
		int x = rand() % 4;
		int y = rand() % 4;
		while (a[x][y] != 0) {
			x = rand() % 4;
			y = rand() % 4;
		}
		a[x][y] = 2;
	}
	else
	{
		int x = rand() % 4;
		int y = rand() % 4;
		while (a[x][y] != 0) {
			x = rand() % 4;
			y = rand() % 4;
		}
		a[x][y] = 4;
	}
	return;
}

int jifen(int a[4][4]) {
	int x = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			x += a[i][j];
	return x;
}

void GameStar() {
	cleardevice();
	int a[4][4] = { 0 };
	int(*p)[4] = a;
	while (1)
	{	
		TCHAR score[20];
		_stprintf(score, _T("Score: %d"), jifen(a));
		outtextxy(100, 100, score);
		if (Move(a)) {
			Sleep(100);
			MakeNew24(p);
			cleardevice();
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					outtextxy(350 + j * 20, 250 + i * 20, a[i][j] + 48);
				}
			}
		}
		
	}
}

int main() {
	initgraph(800, 500);
	ExMessage f;
	outtextxy(350, 250, L"Press F to Star");
	outtextxy(350, 270, L"Press Q to Quit");
	while (true)
	{
		peekmessage(&f, EX_KEY);
		if (f.message==WM_KEYDOWN)
		{
			if (f.vkcode == 'F')
				GameStar();
		}

		if (f.message == WM_KEYDOWN)
		{
			if (f.vkcode == 'Q')
				break;
		}
	}
	return 0;
}