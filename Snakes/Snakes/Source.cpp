#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "console.h"
#define Trucx 100
#define Trucy 30

using namespace std;

enum chay { UP, DOWN,LEFT,RIGHT };

struct chuchay
{
	string a;
	int y, x;
	chay tt;
};

int main()
{
	chuchay b;
	ios_base::sync_with_stdio(false);
	b.a = "BeLeDanDat";
	srand(static_cast<unsigned int>(time(0)));
	b.x = rand() % Trucx;
	b.y = rand() % Trucy;
	b.tt = DOWN;
	while (true)
	{
		clrscr();
		gotoXY(b.x, b.y);
		// di chuyen
		TextColor(rand() % 16);
		cout << b.a;
		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
			case 'a': 
					{
						 b.x--; 
						 b.tt = LEFT;
						 break; 
					}
			case 'd':
					{
						 b.x++;
						 b.tt = RIGHT;
						 break;
					}
			case 'w': 
					{
						 b.y--;
						 b.tt = UP;
						 break;
					}
			case 's':
					{
						b.y++;
						b.tt = DOWN;
						break;
					}
			}
		}
		if (b.y >= Trucy - 1)
			b.tt = UP;
		else if (b.y <= 0)
			b.tt = DOWN;
		else if (b.x >= Trucx - 1)
			b.tt = LEFT;
		else if (b.x <= 0)
			b.tt = RIGHT;
		if (b.tt == DOWN)
			b.y++;
		else if (b.tt == UP)
			b.y--;
		else if (b.tt == LEFT)
			b.x--;
		else if (b.tt == RIGHT)
			b.x++;
		Sleep(100);
	}
}