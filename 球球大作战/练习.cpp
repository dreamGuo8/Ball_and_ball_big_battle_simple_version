/*******************************
* 项目名称：新年烟花
* 开发环境：vs2022 + Easyx
* 作者：轩
* 代码长度：137 行
* 完成时间：2023.1.20
* 用时:2.2 小时
*******************************/

#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define MAXNUM 15
#define WIDTH 640
#define HEIGHT 480
#define PI 3.1415926

struct Fire
{
	int nowx;
	int nowy;
	int endy;
	int radio;
	int explode;
	int rgb[3];
	COLORREF color;
}fire[MAXNUM];

void Init()
{
	for (int i = 0; i < MAXNUM; i++)
	{
		fire[i].nowx = rand() % WIDTH;
		fire[i].nowy = HEIGHT + rand() % 250 + 50;
		fire[i].endy = rand() % 100 + 10;
		fire[i].radio = rand() % 50 + 120;
		fire[i].explode = 0;
		int c[][3] = { {255, 0, 0}, {210, 190, 255}, {255, 120, 0}, {255, 0, 150}, {255, 240, 100}, {10, 255, 255}, {160, 10, 255}, {255, 200, 60} };
		int n = rand() % 8;
		fire[i].color = RGB(c[n][0], c[n][1], c[n][2]);
		fire[i].rgb[0] = c[n][0];
		fire[i].rgb[1] = c[n][1];
		fire[i].rgb[2] = c[n][2];
	}
}

void Draw()
{
	for (int i = 0; i < MAXNUM; i++)
	{
		if (fire[i].nowy > fire[i].endy)
		{
			for (int size = 5; size > 0; size--)
			{
				int temp[] = { fire[i].rgb[0], fire[i].rgb[1], fire[i].rgb[2] };
				for (int k = 0; k < 3; k++)
				{
					temp[k] += 50 * (5 - size);
					if (temp[k] > 255) temp[k] = 255;
				}
				setfillcolor(RGB(temp[0], temp[1], temp[2]));
				solidcircle(fire[i].nowx, fire[i].nowy + 15 * (10 - size), size);
			}
		}
		else
		{
			for (int a = 0; a < 360; a += 30)
			{
				for (int size = 5; size > 0; size--)
				{
					int x = cos(a * PI / 180.0) * (fire[i].explode + size * 10) + fire[i].nowx;
					int y = sin(a * PI / 180.0) * (fire[i].explode + size * 10) + fire[i].nowy + fire[i].radio / 2;
					int temp[] = { fire[i].rgb[0], fire[i].rgb[1], fire[i].rgb[2] };
					for (int k = 0; k < 3; k++)
					{
						temp[k] += 50 * (5 - size);
						if (temp[k] > 255) temp[k] = 255;
					}
					setfillcolor(RGB(temp[0], temp[1], temp[2]));
					solidcircle(x, y + (HEIGHT - y) * 0.1 + size * (size - 2), size);
				}
			}
		}
	}
}

void Move()
{
	for (int i = 0; i < MAXNUM; i++)
	{
		if (fire[i].nowy > fire[i].endy)
		{
			fire[i].nowy -= 3;
		}
		else
		{
			if (fire[i].explode >= fire[i].radio)
			{
				fire[i].nowx = rand() % WIDTH;
				fire[i].nowy = HEIGHT + rand() % 250 + 50;
				fire[i].endy = rand() % 100 + 10;
				fire[i].radio = rand() % 50 + 120;
				fire[i].explode = 0;
				int c[][3] = { {255, 0, 0}, {210, 190, 255}, {255, 120, 0}, {255, 0, 150}, {255, 240, 100}, {10, 255, 255}, {160, 10, 255}, {255, 200, 60} };
				int n = rand() % 8;
				fire[i].color = RGB(c[n][0], c[n][1], c[n][2]);
				fire[i].rgb[0] = c[n][0];
				fire[i].rgb[1] = c[n][1];
				fire[i].rgb[2] = c[n][2];
			}
			else fire[i].explode++;
		}
	}
}

int main()
{
	srand(time(NULL));
	initgraph(640, 480);
	Init();
	BeginBatchDraw();
	while (true)
	{
		cleardevice();
		Draw();
		Move();
		FlushBatchDraw();
		Sleep(2);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}