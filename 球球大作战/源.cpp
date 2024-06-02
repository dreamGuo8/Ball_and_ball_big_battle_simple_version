#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <stdlib.h>     //内含函数
#include <math.h>
#include <stdbool.h>     //定义了一个布尔类型
#define Food_num 250
#define TowPointDistance(spr1,spr2) sqrt(pow((spr1).position.x-(spr2).position.x,2))+pow((spr1).position.y-(spr2).position.y,2)
//pow 平方 ，后面数字是次方    sqrt 根号

ExMessage msg = { 0 };  //消息变量

struct Sprite {
	POINT position;
	POINT veclocity;   //速度,  ponit 是一个点
	int speed;
	float radius;    //食物的半径
	COLORREF color;   //填充颜色
	bool active;
};//封装一个结构

void sprite_init(Sprite* pthis, POINT pos, int radius) {
	pthis->position = pos;  //点坐标
	pthis->veclocity = { 0,0 };//  速率
	pthis->speed = 3;
	pthis->radius = radius;
	pthis->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	pthis->active = true;
}

void sprite_update(Sprite* pthis) {
	pthis->position .x+= pthis->speed * pthis->veclocity.x;
	pthis->position .y+= pthis->speed * pthis->veclocity.y;
}

void sprite_keyboardContral(Sprite* pthis) {
	
		//peekmessage这个函数用于获取一个消息，并立即返回。
	if (msg.message == WM_KEYDOWN) {
		//	WM_KEYDOWN  按键按下消息
		switch (msg.vkcode)//这个结构体用于保存鼠标消息
		{
		case VK_UP:
			pthis->veclocity.y = -1;
			break;

		case VK_DOWN:
			pthis->veclocity.y = 1;
			break;

		case VK_LEFT:
			pthis->veclocity.x = -1;
			break;

		case VK_RIGHT:
			pthis->veclocity.x = 1;
			break;

		}
	}
		else if (msg.message == WM_KEYUP) {
			switch (msg.vkcode)
			{
			case VK_UP:
				pthis->veclocity.y = 0;
				break;

			case VK_DOWN:
				pthis->veclocity.y = 0;
				break;

			case VK_LEFT:
				pthis->veclocity.x = 0;
				break;

			case VK_RIGHT:
				pthis->veclocity.x = 0;
				break;
			}
		}
	
}

void  sprite_draw(Sprite* pthis) {
	if (pthis->active) {
		solidcircle(pthis->position.x, pthis->position.y, pthis->radius);
		setfillcolor(pthis->color);// 填充颜色
	}
	
}

//游戏函数,全局函数
Sprite player;
Sprite foods[Food_num];
int Foodscnt = Food_num;
 

void init() {

	//玩家
	sprite_init(&player, { 50,50 }, 20);


	//食物
	srand(time(NULL));    //srand 初始化随机数发生器
	for (int i = 0; i < Food_num; i++) {
		sprite_init(foods + i, { rand() % getwidth(),rand() % getheight() }, rand() % 4 + 1);
	}

}

void update() {
	sprite_update(&player);
	//判断玩家能否吃到食物
	for (int i = 0; i < Food_num; i++) {
		if (foods[i].active && TowPointDistance(player, foods[i]) < player.radius) {
			player.radius += foods[i].radius / 5;
			foods[i].active = false;
			--Foodscnt;
			//随机产生一个食物
		
			break;
		}
	}
	if (Foodscnt < 100) {
		for (int i = 0; i <Food_num ; i++) {
			if (!foods[i].active) {
				sprite_init(foods + i, { rand() % getwidth(),rand() % getheight() }, rand() % 4 + 1);
				++Foodscnt;
			}
			if (Foodscnt > 105) {
				break;
			}
		}
		
	}
	
}

void draw() {

	BeginBatchDraw();   //开始批量绘图
	cleardevice();     //清除屏幕内容
	                              

	//绘制食物
	for (int i = 0; i < Food_num; i++) {
		//solidcircle(foods[i].position.x, foods[i].position.y, 5);
		sprite_draw(foods + i);
	}

	sprite_draw(&player);       //绘制玩家 

	EndBatchDraw();      //结束批量绘图
}

int main() {
	initgraph(1024, 640, EX_SHOWCONSOLE);//显示控制台 

	setbkcolor(WHITE);//用设置的背景色填充窗口
	cleardevice();

	init();

	//循环
	while (1) {
	
		//setfillcolor(RGB(255, 50, 50));   // 放在生成圆之前，三原色
		//solidcircle(player.position.x, player.position.y, 20);    //生成圆


		if (peekmessage(&msg)) {
			sprite_keyboardContral(&player);
		}
		update();
		draw();
		
		sprite_draw(&player);              //生成圆,函数,绘制玩家	

		sprite_update(&player);
		
		Sleep(10);

	}
	getchar();  //等待一下，防止闪退
	return 0;
}

