#pragma once
#include <fstream>
#include <Windows.h>
#include <easyx.h>
using namespace std;

void opear(ExMessage m) {
	ofstream fout;
	fout.open("Opeartional_Process.txt", ios::app);
	if (m.vkcode != 'Q' && m.vkcode != 'R')
		fout << m.vkcode;
	else
		fout <<"end" << '\n';
	fout.close();
}

void scoreinput(int score) {
	ofstream fout;
	fout.open("score.txt", ios::app);
	fout << "score:" << score << '\n';
	fout.close();
}