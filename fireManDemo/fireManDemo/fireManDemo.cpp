#include <graphics.h>
#include <stdio.h>
#include <time.h>
//通用属性类的数字用英语表示
//人物站着宽度和高度
#define WIDTH 640
#define HEIGHT 400
#define ROLE_IMGW 70
#define ROLE_IMGH 100
//地板的高度
#define FLOOR_Y 360
//人物站在地板上的坐标
#define BEGIN_X 50
#define BEGIN_Y  FLOOR_Y-ROLE_IMGH
//跳跃到大的最高点
#define JUMP_MIN_Y 60
//滚动的图像的宽度和高度
#define ROLL_IMGW 50
#define ROLL_IMGH 50
#define MAX_FRAME 8


IMAGE jumpIMG;
IMAGE rollIMG[8];
IMAGE runIMG[8];
int frameNum = 0;		//帧数控制
int speed = -10;		//开始跳跃是往上走的

//人物的状态枚举出来
enum State {Run,Roll,Jump};	 //整形常量 ，用英语单词表示整数	
//人物的属性
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
//加载资源
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
	settextstyle(80, 0, "叶根友疾风草书");
	outtextxy(100, 100, "奔跑的火柴人");
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
	1.喜欢我的课，能接受顿开方式 (直播+录播，2 4 6  所有课程内容时间8-9月)
		1.1 课程内容很多： C语言 C++ windows Qt 数据结构与算法 Linux   OpenCV 多线程 数据库....
	2.坚持学习
		2.1 大家拓展到其他方向   应用程序开发   游戏开发
		2.2 语言是工具，看你自己的亲和力  任何语言都有高薪人才，就看能不能钻研
	3.主动问问题  --->一对一解答过程：微信消息，QQ， QQ远程，向日葵远程
	4.完成作业--->编程是一个积累过程
	//没有活动 
	//今天莫影老师课堂入学成功同学
	//仅限3个同学
	1.依旧享受学费减免1000
	2.鼠标套装+百度会员一年
	3.终身制
	4.外包福利优先获取





*/
