/*
	1.ͼ�δ��ڵĴ���
		1.1 easyxͼ�ο�-->�Լ���װ
		1.2 ����ͼ�ο�ͷ�ļ� #include <graphics.h>
		1.3 printf�����Ǵ�ӡ��initgraph(int w,int h);
		1.4 �رմ���: closegraph();
		1.5 ��������
			1.5.1 ������ɫ: setbkcolor(��ɫ)
					1.5.1.1 ��ɫ��Ӣ���д����   RED  WHITE
					1.5.1.2 RGB������ɫ
			1.5.2 ˢ��: cleardevice();
		1.6 ��������
	2.������� C���� printf ��Ŀ���Ը�Ϊ���ֽ�
		2.1 outtextxy(int x,int y,const char* str);
		2.2 ������ʽ
			2.2.1 ������ɫ�� settextcolor(��ɫ)
			2.2 2 ��������:  settextstyle(int h,int w,const char* mode); mode��ʾ��������
	3.ͼ����ʾ
		3.1 ������ͼ����������
			3.1.1 solidrectangle(int x,int y,int xx,int yy);
			3.1.2 ���������ɫ setfillcolor(��ɫ);
		3.2 ��ͼ������
			3.2.1  ������	int a;   IMAGE img
			3.2 2  ������ϵ  scanf;   loadimage(&img,"imgURL");  loadimage(&img,"imgURL",int w,int h)
			3.2.3  ��ʾͼ��	printf;  putimage(int x,int y,IMAGE* img);
	4.��ʱ��
*/
#include <stdio.h>
#include <graphics.h>
#include "tools.hpp"
void DrawFloor() 
{
	//setbkcolor(WHITE);
	//cleardevice();
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, "Ҷ���Ѽ������");
	outtextxy(100, 100, "���ܵĻ����");
	setfillcolor(LIGHTBLUE);
	solidrectangle(0, 360, 640, 400);
}

int main() 
{
	initgraph(640, 400);

	IMAGE mm;
	loadimage(&mm, "./7.jpg", 640, 400);
	putimage(0, 0, &mm);
	DrawFloor();
	IMAGE boy;
	loadimage(&boy, "./boy.png");
	drawImg(0, 0, &boy);


	while (1);
	closegraph();
	return 0;
}
