#include <iostream>
#include "console.h"
#include <ctime>
#include <Windows.h>
#include <conio.h>
#define Col		39
#define Line	29
using namespace std;

struct HinhDang {
	char a[5][5];
	int color[5][5];
};
struct ToaDo {
	int x, y;
};

struct ToaDoDiem {
	int x, y;
	bool an = false;
};

struct Xe {
	ToaDo td[2];
	HinhDang hd;
};

struct VatCan {
	ToaDoDiem td[2];
	HinhDang hd;
};

int ViTri(int Toado) {
	int Hang = Toado % 4;
	switch (Hang)
	{
	case 0: 
		return 4;
		break;
	case 1:
		return 14;
		break;
	case 2:
		return 24;
		break;
	case 3:
		return 34;
	}
}

void KhoiTao(Xe &xe,VatCan &vc) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			xe.hd.a[i][j] = 15;
			vc.hd.color[i][j] = 15;
		}
	}
	srand(time(NULL));
	vc.td[1].x = ViTri(rand());
	vc.td[1].y = -3;
	vc.td[0].x = ViTri(rand());
	vc.td[0].y = -13;
	for (int i = 0; i <= 4; i++) {
		for (int j = 0; j <= 4; j++) {
			vc.hd.a[i][j] = '!';
		}
	}
	xe.td[0].x = ViTri(rand() % 2);
	xe.td[1].x = ViTri(rand() % 2 + 2);
	xe.td[0].y = xe.td[1].y = Line - 2;
	xe.hd.a[0][0] = xe.hd.a[0][4] = xe.hd.a[4][0] = xe.hd.a[4][4] = 'O';
	xe.hd.color[0][0] = xe.hd.color[0][4] = xe.hd.color[4][0] = xe.hd.color[4][4] = 4;
	for (int i = 1; i <= 3; i++)
	{ 
		xe.hd.a[0][i] = '^';
		xe.hd.color[0][i] = 2;
		xe.hd.a[i][0] = xe.hd.a[i][4] = '|';
		xe.hd.color[i][0] = xe.hd.color[i][4] = 12;
		xe.hd.a[4][i] = '-';
		xe.hd.color[4][i] = 8;
		for (int j = 1; j <= 3; j++) { xe.hd.a[i][j] = 'A'; xe.hd.color[i][j] = 3; }
	}

}

void HienThi(Xe xe,VatCan vc,int diem) {
	for (int i = 0; i <= Line; i++) {
		TextColor(15);
		gotoXY(0, i);
		putchar(186);
		gotoXY(Col, i);
		putchar(186);
		for (int j = 9; j < Col; j += 10) {
			gotoXY(j, i);
			if (j == 19) putchar(186);
			else if ((i+2) % 6 <= 3) putchar(219);
			else putchar(' ');
		}
	}
	for (int i = 1; i >= 0; --i) {
		for (int dong = -2; dong <= 2; ++dong) {
			for (int cot = -2; cot <= 2; ++cot) {
				int x = xe.td[i].x + cot;
				int y = xe.td[i].y + dong;
				gotoXY(x, y);
				TextColor(xe.hd.color[dong + 2][cot + 2]);
				putchar(xe.hd.a[dong + 2][cot + 2]);
				int xCan = vc.td[i].x + cot;
				int yCan = vc.td[i].y + dong;
				if (yCan >= 0 && yCan <= Line) {
					gotoXY(xCan, yCan);
					TextColor(vc.hd.color[dong + 2][cot + 2]);
					putchar(vc.hd.a[dong + 2][cot + 2]);
				}
			}
		}
	}
	gotoXY(47, 15);
	TextColor(15);
	std::cout << "Score: " << diem;
}

void XuLi(Xe &xe, VatCan &vc, int &diem) {
	if (_kbhit()) {
		int key = _getch();
		if (key == 'a' || key == 'A') {
			if (xe.td[0].x == ViTri(0)) xe.td[0].x = ViTri(1);
			else xe.td[0].x = ViTri(0);
		}
		if (key == 'd' || key == 'D') {
			if (xe.td[1].x == ViTri(2)) xe.td[1].x = ViTri(3);
			else xe.td[1].x = ViTri(2);
		}
	}
	for (int i = 0; i <= 1; i++)
	{
		if (vc.td[i].y <= 31) vc.td[i].y+=2;
		else {
			vc.td[i].y = -3;
			srand(time(NULL));
			vc.td[i].x = ViTri(rand());
			vc.td[i].an = false;
		}
		for (int j = 0; j <= 1; j++){
			if (xe.td[j].y <= vc.td[i].y && vc.td[i].an == false) {
				diem++;
				vc.td[i].an = true;
			}
		}
	}
}

bool GameOver(Xe xe, VatCan vc) {
	for (int i = 0; i <= 1; i++) {
		for (int hang = -2; hang <= 2; ++hang) {
			for (int cot = -2; cot <= 2; ++cot) {
				int x = xe.td[i].x + cot;
				int y = xe.td[i].y + hang;
				for (int hangI = -2; hangI <= 2; ++hangI) {
					for (int cotI = -2; cotI <= 2; ++cotI) {
						int xC = vc.td[i].x + cotI;
						int yC = vc.td[i].y + hangI;
						if (xC == x && yC == y) return true;
					}
				}
			}
		}
	}
	return false;
}

int main() {
	Xe xe;
	VatCan vc;
	int diem = 0;
	KhoiTao(xe,vc);
	while (true)
	{
		clrscr();
		HienThi(xe,vc,diem);
		XuLi(xe,vc,diem);
		if (GameOver(xe, vc)) break;
		Sleep(200);
	}
}