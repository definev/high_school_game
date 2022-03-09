/*Di chuyển nhân vật 'a' và 'd'
Enter để endgame
Have fun !!! :))))))
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"
#define gtl(i) {gotoXY(16,i);for (int j = 1; j <= 3; ++j) cout << char(178);}
#define gtr(i) {gotoXY(22, i);for (int j = 1; j <= 3; ++j) cout << char(178);}

#define timbermove(i)	{gotoXY(i, 19); cout << 'W'; gotoXY(i, 18); cout << '+'; }
using namespace std;

enum brand {LEFT,RIGHT,NON};

struct tree
{
	brand a[20];
};

struct timber
{
	brand x;
};
void inboard()
{
	gotoXY(0, 0);
	for (int i = 0; i < 40; ++i) cout << char(178);
	gotoXY(0, 0);
	for (int i = 0; i < 20; ++i) cout << char(178) << endl;
	for (int j = 19; j <= 21; ++j)
	{
		for (int i = 0; i < 21; ++i)
		{
			gotoXY(j, i);
			cout << char(178);
		}
	}
	gotoXY(0, 20);
	for (int i = 0; i < 40; ++i) cout << char(178);
	gotoXY(40, 0);
	for (int i = 0; i < 21; ++i)
	{
		gotoXY(40, i);
		cout << char(178);
	}
}

void khoitao(tree & tree,timber &timber)
{
	timber.x = LEFT;
	for (int i = 1; i <= 17; i++)
	{
		if (i % 2 == 0)
		{
			if (rand() % 2 == 1) tree.a[i] = LEFT;
			else tree.a[i] = RIGHT;
		}
		else tree.a[i] = NON;
	}
}

void hienthi(tree tree,timber timber,int score)
{
	clrscr();
	gotoXY(45, 10);
	cout << "Score: " << score;
	inboard();
	if (timber.x == LEFT) timbermove(15)
	if (timber.x == RIGHT) timbermove(25)
	for (int i = 18; i > 0; --i)
	{
		if (tree.a[i] == LEFT) gtl(i)
		if (tree.a[i] == RIGHT) gtr(i)
	}
}

bool gameover(tree tree, timber timber)
{
	if (tree.a[18] == timber.x) return true;
	return false;
}
void trangthai(timber &timber)
{
	char key = _getch();
	if (key == 'A' || key == 'a') timber.x = LEFT;
	if (key == 'D' || key == 'd') timber.x = RIGHT;
}

void xuli(tree &tree, timber timber,int &score)
{
	if (tree.a[18] != timber.x)
	{
		score++;
		for (int i = 18; i >= 1; --i) tree.a[i + 1] = tree.a[i];
		if (tree.a[2] == NON)
		{
			srand(time(NULL));
		if (rand() % 2 == 1) tree.a[1] = LEFT;
			else tree.a[1] = RIGHT;
		}
		else tree.a[1] = NON;
	}
	else clrscr();
}

int main()
{
	srand(time(NULL));
	tree tree;
	timber timber;
	int score = 0;
	khoitao(tree,timber);
	while (1)
	{
		hienthi(tree, timber,score);
		trangthai(timber);
		xuli(tree, timber,score);
		if (gameover(tree,timber))
		{
			clrscr();
			gotoXY(36, 15);
			cout << "GAME OVER!!!";
			while (_getch() != 13);
			break;
		}
		Sleep(100);
	}
}