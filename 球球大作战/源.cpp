#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <stdlib.h>     //�ں�����
#include <math.h>
#include <stdbool.h>     //������һ����������
#define Food_num 250
#define TowPointDistance(spr1,spr2) sqrt(pow((spr1).position.x-(spr2).position.x,2))+pow((spr1).position.y-(spr2).position.y,2)
//pow ƽ�� �����������Ǵη�    sqrt ����

ExMessage msg = { 0 };  //��Ϣ����

struct Sprite {
	POINT position;
	POINT veclocity;   //�ٶ�,  ponit ��һ����
	int speed;
	float radius;    //ʳ��İ뾶
	COLORREF color;   //�����ɫ
	bool active;
};//��װһ���ṹ

void sprite_init(Sprite* pthis, POINT pos, int radius) {
	pthis->position = pos;  //������
	pthis->veclocity = { 0,0 };//  ����
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
	
		//peekmessage����������ڻ�ȡһ����Ϣ�����������ء�
	if (msg.message == WM_KEYDOWN) {
		//	WM_KEYDOWN  ����������Ϣ
		switch (msg.vkcode)//����ṹ�����ڱ��������Ϣ
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
		setfillcolor(pthis->color);// �����ɫ
	}
	
}

//��Ϸ����,ȫ�ֺ���
Sprite player;
Sprite foods[Food_num];
int Foodscnt = Food_num;
 

void init() {

	//���
	sprite_init(&player, { 50,50 }, 20);


	//ʳ��
	srand(time(NULL));    //srand ��ʼ�������������
	for (int i = 0; i < Food_num; i++) {
		sprite_init(foods + i, { rand() % getwidth(),rand() % getheight() }, rand() % 4 + 1);
	}

}

void update() {
	sprite_update(&player);
	//�ж�����ܷ�Ե�ʳ��
	for (int i = 0; i < Food_num; i++) {
		if (foods[i].active && TowPointDistance(player, foods[i]) < player.radius) {
			player.radius += foods[i].radius / 5;
			foods[i].active = false;
			--Foodscnt;
			//�������һ��ʳ��
		
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

	BeginBatchDraw();   //��ʼ������ͼ
	cleardevice();     //�����Ļ����
	                              

	//����ʳ��
	for (int i = 0; i < Food_num; i++) {
		//solidcircle(foods[i].position.x, foods[i].position.y, 5);
		sprite_draw(foods + i);
	}

	sprite_draw(&player);       //������� 

	EndBatchDraw();      //����������ͼ
}

int main() {
	initgraph(1024, 640, EX_SHOWCONSOLE);//��ʾ����̨ 

	setbkcolor(WHITE);//�����õı���ɫ��䴰��
	cleardevice();

	init();

	//ѭ��
	while (1) {
	
		//setfillcolor(RGB(255, 50, 50));   // ��������Բ֮ǰ����ԭɫ
		//solidcircle(player.position.x, player.position.y, 20);    //����Բ


		if (peekmessage(&msg)) {
			sprite_keyboardContral(&player);
		}
		update();
		draw();
		
		sprite_draw(&player);              //����Բ,����,�������	

		sprite_update(&player);
		
		Sleep(10);

	}
	getchar();  //�ȴ�һ�£���ֹ����
	return 0;
}

