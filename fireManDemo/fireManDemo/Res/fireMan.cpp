#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROLE_IMGW 70
#define ROLE_IMGH 100
#define FLOOR_Y   360
#define BEGIN_X 50
#define BEGIN_Y FLOOR_Y-ROLE_IMGH
#define JUMP_MIN_Y 60
#define ROLL_IMGW 50
#define ROLL_IMGH 50
enum Sate {Run,Roll,Jump};
IMAGE rollIMG[8];
IMAGE runIMG[8];
IMAGE jumpIMG;
int frameNum = 0;
int speed = -10;
struct FireMan 
{
	int x;
	int y;
	Sate state;
	int w;
	int h;
};
int GetHeight(Sate state) 
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
int GetWidth(Sate state)
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
void DrawFloor() 
{
	setfillcolor(LIGHTBLUE);
	solidrectangle(0, 360, 640, 400);
}
struct FireMan fireMan = { BEGIN_X,BEGIN_Y ,Run,GetWidth(Run),GetHeight(Run)};
void DrawRole() 
{
	switch (fireMan.state) 
	{
	case Run:
		putimage(fireMan.x, fireMan.y, runIMG + frameNum);
		break;
	case Roll:
		putimage(fireMan.x, fireMan.y, rollIMG+frameNum);
		break;
	case Jump:
		putimage(fireMan.x, fireMan.y, &jumpIMG);
		break;
	}
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
		//fireMan.y = BEGIN_Y - GetHeight(Jump);
		//printf("%d\n", fireMan.state);
	}
}
//定时器
int  Timer(int num, int id)
{
	static int start[10] ;
	if (start[id] == 0) 
	{
		start[id] = clock();
	}
	int end = clock();
	if (end - start[id]>num)
	{
		start[id] = end;
		return 1;
	}
	return 0;
}
void MoveRole()
{
	frameNum++;
	switch (fireMan.state)
	{
	case Run:
		if (frameNum == 8)
		{
			frameNum = 0;
		}
		fireMan.y = BEGIN_Y;
		break;
	case Roll:
		if (frameNum == 8)
		{
			frameNum = 0;
		}
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
void LoadResouces() 
{
	loadimage(&jumpIMG, "./Res/Jump/jump.jpg", ROLE_IMGW, ROLE_IMGH);
	char fileName[50] = { "" };
	for (int i = 1; i <= 8; i++) 
	{
		sprintf_s(fileName, 50, "./Res/Roll/gun8_%d.jpg", i);
		loadimage(rollIMG + i - 1, fileName, ROLL_IMGW, ROLL_IMGH);
		sprintf_s(fileName, 50, "./Res/Run/move8_%d.jpg", i);
		loadimage(runIMG + i - 1, fileName, ROLE_IMGW, ROLE_IMGH);
	}
}

int main() 
{
	initgraph(640, 400);
	LoadResouces();
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	while (1) 
	{
		cleardevice();
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(80, 0, "叶根友疾风草书");
		outtextxy(100, 100, "奔跑的火柴人");
		DrawFloor();
		DrawRole();  
		FlushBatchDraw();
		KeyDown();
		if(Timer(20,0))
			MoveRole();
	}
	EndBatchDraw();
	return 0;
}