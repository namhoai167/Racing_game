#pragma once
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <list>
#include <string.h>
#include "Console.h"

extern void huongdan();
extern void scoreMenu();
extern void play(bool auto_play = false);

#define CHIEU_RONG 30
#define CHIEU_DAI 25

#define LIGHT_RED 12
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define WHITE 15
#define RED 4
#define YELLOW 14

#define MAX_PLAYER_NAME 26

struct Cell
{
	unsigned char character;
	unsigned int color;
};

struct ToaDo
{
	int x, y;
};

//Xe
struct Car
{
	ToaDo td;
	char hd_xe[3][3];
};

//Vat can
struct Barrier
{
	ToaDo td;
	int state = 0;	
	//0: bt
	//1: bi dan ban trung
	// co the tuy bien bien thanh hinh dang bat ky qua ham set hinh dang
	char hd_vc[3][3];
};

struct Coin
{
	ToaDo td;
	char hd = '$';
};

//Dan
struct Bullet
{
	ToaDo td;
	char hd = 248;	//giong chu 'o'
};

struct Record
{
	char name[MAX_PLAYER_NAME] = {};
	unsigned int score;
};

void mainMenu();
//extern void huongdan();

int random(int start, int end)
{
	return start + rand() % (end + 1 - start);
}

void showBackButton(int x = -1, int y = -1) {
	if (x != -1 && y != -1)
		gotoXY(x, y);
	setColor(LIGHT_RED);
	printf("Back.");
	while (_getch() != 13);
}

void showMenu(const char *label[], int len, int &index, int selected_color, int x_start, int y_start)
{
	int key = 0;

	setColor(WHITE);
	while (_kbhit()) _getch();	//clear input buffer: loi khi di chuyen theo chieu doc, menu pause xay ra loi

	while (key != 13)
	{
		for (int i = 0; i < len; i++)
		{
			gotoXY(x_start, y_start + i);
			
			if (index != i + 1) {	//unselected
				printf(label[i]);
				continue;
			}

			setColor(selected_color);
			printf(label[i]);
			setColor(WHITE);
		}
		key = _getch();
		if (key == 80)
		{
			index++;
		}
		if (key == 72)
		{
			index--;
		}
		if (index == len + 1)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = len;
		}
	}
}

void hideMenu(int len, int x_start, int y_start)
{
	for (int i = 0; i < len; i++)
	{
		gotoXY(x_start, y_start + i);
		printf("                        ");
	}
}


void mainMenu()
{
	system("cls");		//xóa màn hình, ví dụ người dùng từ mục điểm cao trở ra, pbải xóa màn hình của giao diện điểm cao.
						//nếu người dùng không trở ra từ ""Tiếp tục'" thì không có dòng Nhan 9 de tiep tuc.			
	gotoXY(8, 0);
	setColor(15);
	printf("RACING GAME");

	int index = 1;
	int n_label = 5;
	const char *label[] = { "New game.", "High scores.", "CPU vs CPU.", "Help.", "Exit." };

	showMenu(label, n_label, index, LIGHT_RED, 8, 2);

	//điều kiện chạy thuật toán.
	switch (index) {
		case 1:
			play();
			return;
		case 2:
			scoreMenu();
			return;
		case 3:
			play(true);
			return;
		case 5:
			exit(0);
		case 4:
			huongdan();
			showBackButton(16, 7);
			mainMenu();		//ép buộc người dùng nhấn Enter để trở về menu chính.
			return;
	}

}

/*void oldmainMenu()
{
	system("cls");		//xóa màn hình, ví dụ người dùng từ mục điểm cao trở ra, pbải xóa màn hình của giao diện điểm cao.
						//nếu người dùng không trở ra từ ""Tiếp tục'" thì không có dòng Nhan 9 de tiep tuc.
	int key = 0;
	int index = 1;
	while (key != 13)
	{
		//system("cls");
		gotoXY(8, 0);
		setColor(15);
		printf("RACING GAME");

		setColor(15);		//Màu trắng
		if (index == 1)
		{
			setColor(12);		//Nếu được chon sẽ chuyển thành màu đỏ
		}
		gotoXY(8, 2);
		printf("New game.\n");

		setColor(15);
		if (index == 2)
		{
			setColor(12);
		}
		gotoXY(8, 3);
		printf("High scores.\n");

		setColor(15);
		if (index == 3)
		{
			setColor(12);
		}
		gotoXY(8, 4);
		printf("CPU vs CPU.\n");

		setColor(15);
		if (index == 4)
		{
			setColor(12);
		}
		gotoXY(8, 5);
		printf("Help.\n");

		setColor(15);
		if (index == 5)
		{
			setColor(12);
		}
		gotoXY(8, 6);
		printf("Exit.\n");

		key = _getch();
		if (key == 80)
		{
			++index;
		}
		else if (key == 72)
		{
			--index;
		}
		if (index == 6)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = 5;
		}
	}

	//điều kiện chạy thuật toán.
	if (index == 1) play();
	if (index == 2) scoreMenu();
	if (index == 4) { 
		huongdan(); 

		gotoXY(16, 7);
		setColor(12);
		printf("Back.");
		while (_getch() != 13);
		mainMenu();		//ép buộc người dùng nhấn Enter để trở về menu chính.
	}

	// con lai se thoat
	//if (index == 5 || index == 0)  return;
}*/