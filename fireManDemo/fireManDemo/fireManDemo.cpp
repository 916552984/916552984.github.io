#include <graphics.h>
#include <stdio.h>
#include <time.h>
//ͨ���������������Ӣ���ʾ
//����վ�ſ�Ⱥ͸߶�
#define WIDTH 640
#define HEIGHT 400
#define ROLE_IMGW 70
#define ROLE_IMGH 100
//�ذ�ĸ߶�
#define FLOOR_Y 360
//����վ�ڵذ��ϵ�����
#define BEGIN_X 50
#define BEGIN_Y  FLOOR_Y-ROLE_IMGH
//��Ծ�������ߵ�
#define JUMP_MIN_Y 60
//������ͼ��Ŀ�Ⱥ͸߶�
#define ROLL_IMGW 50
#define ROLL_IMGH 50
#define MAX_FRAME 8


IMAGE jumpIMG;
IMAGE rollIMG[8];
IMAGE runIMG[8];
int frameNum = 0;		//֡������
int speed = -10;		//��ʼ��Ծ�������ߵ�

//�����״̬ö�ٳ���
enum State {Run,Roll,Jump};	 //���γ��� ����Ӣ�ﵥ�ʱ�ʾ����	
//���������
struct FireMan 
{
	int x;
	int y;
	State state;
	int w;
	int h;
};


int GetHeight(State state) 
{
	switch (state) 
	{
	case Run:
	case Jump:
		return ROLE_IMGH;
	case Roll:
		return ROLL_IMGH;
	}
	return 0;
}
int GetWidth(State state)
{
	switch (state)
	{
	case Run:
	case Jump:
		return ROLE_IMGW;
	case Roll:
		return ROLL_IMGW;
	}
	return 0;
}
struct FireMan fireMan = { BEGIN_X,BEGIN_Y,Run, GetWidth(Run),GetHeight(Run) };
//������Դ
void LoadResouces() 
{
	loadimage(&jumpIMG, "./Res/Jump/jump.jpg", ROLE_IMGW, ROLE_IMGH);
	char fileURL[50] = { "" };
	for (int i = 1; i <= 8; i++) 
	{
		sprintf_s(fileURL, 50, "./Res/Roll/gun8_%d.jpg", i);
		loadimage(rollIMG + i - 1, fileURL, ROLL_IMGW, ROLL_IMGH);
		sprintf_s(fileURL, 50, "./Res/Run/move8_%d.jpg", i);
		loadimage(runIMG + i - 1, fileURL, ROLE_IMGW, ROLE_IMGH);
	}
}

void DrawRole() 
{
	switch (fireMan.state) 
	{
	case Run:
		putimage(fireMan.x, fireMan.y, runIMG + frameNum);
		break;
	case Roll:
		putimage(fireMan.x, fireMan.y, rollIMG + frameNum);
		break;
	case Jump:
		putimage(fireMan.x, fireMan.y, &jumpIMG);
		break;
	}
}

int Timer(int duration, int id)
{
	static int startTime[10];
	if (startTime[id] == 0) 
	{
		startTime[id] = clock();
	}
	int endTime = clock();
	if (endTime - startTime[id] >= duration) 
	{
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

void KeyDown() 
{
	if (GetAsyncKeyState(VK_SPACE)) 
	{
		fireMan.state = Roll;
		fireMan.y = BEGIN_Y + GetHeight(Roll);
	}
	if (GetAsyncKeyState(VK_UP)) 
	{
		fireMan.state = Jump;
	}
}

void MoveRole() 
{
	frameNum++;
	switch (fireMan.state) 
	{
	case Run:
		if (frameNum == MAX_FRAME)
		{
			frameNum = 0;
		}
		fireMan.y = BEGIN_Y;
		break;
	case Roll:
		if (frameNum == MAX_FRAME)
			frameNum = 0;
		if (Timer(500, 1)) 
		{
			fireMan.state = Run;
			fireMan.y = BEGIN_Y;
		}
		break;
	case Jump:
		frameNum = 0;
		if (fireMan.y < JUMP_MIN_Y) 
		{
			speed = -speed;
		}
		fireMan.y += speed;
		if (fireMan.y >= BEGIN_Y) 
		{
			fireMan.y = BEGIN_Y;
			speed = -speed;
			fireMan.state = Run;
		}
		break;
	}
}

void DrawFloor()
{
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, "Ҷ���Ѽ������");
	outtextxy(100, 100, "���ܵĻ����");
	setfillcolor(LIGHTBLUE);
	solidrectangle(0, 360, 640, 400);
}
int main() 
{
	LoadResouces();
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	while (1) 
	{
		DrawFloor();
		DrawRole();
		FlushBatchDraw();
		if(Timer(20,0))
			MoveRole();
		KeyDown();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
/*
	1.ϲ���ҵĿΣ��ܽ��ܶٿ���ʽ (ֱ��+¼����2 4 6  ���пγ�����ʱ��8-9��)
		1.1 �γ����ݺࣺܶ C���� C++ windows Qt ���ݽṹ���㷨 Linux   OpenCV ���߳� ���ݿ�....
	2.���ѧϰ
		2.1 �����չ����������   Ӧ�ó��򿪷�   ��Ϸ����
		2.2 �����ǹ��ߣ������Լ����׺���  �κ����Զ��и�н�˲ţ��Ϳ��ܲ�������
	3.����������  --->һ��һ�����̣�΢����Ϣ��QQ�� QQԶ�̣����տ�Զ��
	4.�����ҵ--->�����һ�����۹���
	//û�л 
	//����ĪӰ��ʦ������ѧ�ɹ�ͬѧ
	//����3��ͬѧ
	1.��������ѧ�Ѽ���1000
	2.�����װ+�ٶȻ�Աһ��
	3.������
	4.����������Ȼ�ȡ





*/
