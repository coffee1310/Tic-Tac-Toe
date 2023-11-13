#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Mmsystem.h"
#pragma comment(lib, "winmm")

using namespace std;

const int ROW = 3;
const int COL = 3;

int area[ROW][COL] = { {0, 0, 0}, {0, 0, 0 }, {0, 0, 0} };
int area_front[ROW][COL] = { {1, 0, 0}, {0, 0, 0 }, {0, 0, 0} };
int counter = 0;
int x = 0;
int y = 0;
int player = 1;

void print_area() {
	system("cls");

	cout << "Крестики-нолики" << endl;
	cout << "Ход игрока " << player << endl;

	for (int i = 0; i < ROW; i++) {
		cout << "|";
		for (int j = 0; j < COL; j++) {
			if (area_front[i][j] == 0) {
				cout << "_";
			}
			else if (area_front[i][j] == 1) {
				cout << "#";
			}
			else if (area_front[i][j] == 2) {
				cout << "X";
			}
			else if (area_front[i][j] == 3) {
				cout << "O";
			}
			cout << "|";
		}
		cout << endl;
	}
}

void copy_area() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			area_front[i][j] = area[i][j];
		}
	}
}

void change_pos() {
	copy_area();
	area_front[y][x] = 1;
	print_area();
}

int check_area() {
	// Игрок 1
	if (area[0][0] == 2 && area[0][1] == 2 && area[0][2] == 2) {
		return 1;
	}
	if (area[1][0] == 2 && area[1][1] == 2 && area[1][2] == 2) {
		return 1;
	}
	if (area[2][0] == 2 && area[2][1] == 2 && area[2][2] == 2) {
		return 1;
	}
	if (area[0][0] == 2 && area[1][0] == 2 && area[2][0] == 2) {
		return 1;
	}
	if (area[0][1] == 2 && area[1][1] == 2 && area[2][1] == 2) {
		return 1;
	}
	if (area[0][2] == 2 && area[1][2] == 2 && area[2][2] == 2) {
		return 1;
	}
	if (area[0][0] == 2 && area[1][1] == 2 && area[2][2] == 2) {
		return 1;
	}
	if (area[0][2] == 2 && area[1][1] == 2 && area[2][0] == 2) {
		return 1;
	}

	// Игрок 2
	if (area[0][0] == 3 && area[0][1] == 3 && area[0][2] == 3) {
		return 2;
	}
	if (area[1][0] == 3 && area[1][1] == 3 && area[1][2] == 3) {
		return 2;
	}
	if (area[2][0] == 3 && area[2][1] == 3 && area[2][2] == 3) {
		return 2;
	}
	if (area[0][0] == 3 && area[1][0] == 3 && area[2][0] == 3) {
		return 2;
	}
	if (area[0][1] == 3 && area[1][1] == 3 && area[2][1] == 3) {
		return 2;
	}
	if (area[0][2] == 3 && area[1][2] == 3 && area[2][2] == 3) {
		return 2;
	}
	if (area[0][0] == 3 && area[1][1] == 3 && area[2][2] == 3) {
		return 2;
	}
	if (area[0][2] == 3 && area[1][1] == 3 && area[2][0] == 3) {
		return 2;
	}

	return 0;
}
void enter_sym() {
	if (area[y][x] != 2 && area[y][x] != 3) {
		if (player == 1) {
			area[y][x] = 2;
			player = 2;
			PlaySound(TEXT("change_cell.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else {
			area[y][x] = 3;
			player = 1;
			PlaySound(TEXT("change_cell.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		copy_area();
		x = 0;
		y = 0;
		counter++;
		cout << counter;
	}
	else
	{
		PlaySound(TEXT("incorrect_change.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void move_pos(int ch) {
	if (ch == 72) {
		if (y == 0)
			y = 2;
		else
			y--;

	}
	if (ch == 80) {
		if (y == 2)
			y = 0;
		else 
			y++;

	}
	if (ch == 75) {
		if (x == 0)
			x = 2;
		else
			x--;

	}
	if (ch == 77) {
		if (x == 2)
			x = 0;
		else
			x++;
	}
	if (ch == 13) {
		enter_sym();
	}
	change_pos();
}

void main()
{
	setlocale(LC_ALL, "ru");
	int code;
	int ch;

	print_area();
	
	while (check_area() == 0 && counter < 9) {
		if (kbhit()) {
			ch = getch();
			move_pos(ch);
		}
	}

	Sleep(100);
	if (check_area() == 1) {
		cout << "Игрок 1 выиграл!";
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if (check_area() == 2) {
		cout << "Игрок 2 выиграл!";
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else {
		cout << "Ничья!";
		PlaySound(TEXT("lose.wav"),NULL, SND_FILENAME | SND_ASYNC);
	}
	Sleep(1000);
}