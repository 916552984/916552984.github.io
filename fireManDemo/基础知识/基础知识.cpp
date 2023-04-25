/*
	1.图形窗口的创建
		1.1 easyx图形库-->自己安装
		1.2 包含图形库头文件 #include <graphics.h>
		1.3 printf函数是打印，initgraph(int w,int h);
		1.4 关闭窗口: closegraph();
		1.5 窗口属性
			1.5.1 背景颜色: setbkcolor(颜色)
					1.5.1.1 颜色的英语大写单词   RED  WHITE
					1.5.1.2 RGB配置颜色
			1.5.2 刷新: cleardevice();
		1.6 窗口坐标
	2.文字输出 C语言 printf 项目属性改为多字节
		2.1 outtextxy(int x,int y,const char* str);
		2.2 文字样式
			2.2.1 文字颜色： settextcolor(颜色)
			2.2 2 文字字体:  settextstyle(int h,int w,const char* mode); mode表示字体名字
	3.图像显示
		3.1 基本绘图：画填充矩形
			3.1.1 solidrectangle(int x,int y,int xx,int yy);
			3.1.2 设置填充颜色 setfillcolor(颜色);
		3.2 贴图三步曲
			3.2.1  起名字	int a;   IMAGE img
			3.2 2  建立联系  scanf;   loadimage(&img,"imgURL");  loadimage(&img,"imgURL",int w,int h)
			3.2.3  显示图像	printf;  putimage(int x,int y,IMAGE* img);
	4.定时器
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
	settextstyle(80, 0, "叶根友疾风草书");
	outtextxy(100, 100, "奔跑的火柴人");
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
