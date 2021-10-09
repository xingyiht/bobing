#include<graphics.h>
#include<string>
#include <cstring>
#include<iostream>
#include<graphics.h>
#include<windows.h>
#include<ctype.h>
#include<string.h>
#include<stack> 
#include<fstream>
#include<cassert>
#include<ctime>
#include <stdlib.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
using namespace std;
class button
{
public:
	int x;
	int y;//(x,y)按键左上角的位置
	int width;//按键宽度
	int height;//按键高度
	COLORREF color;//按键的颜色，颜色全部都是大写的英文单词
	char* str;//按键上的字
	void build(int x_, int y_, int width_, int height_, COLORREF color_, const char* str_) //对按键进行初始化，这里也可以直接用构造函数
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
		color = color_;
		str = new char[strlen(str_) + 1];//字符指针需要预先分配内存
		strcpy(str, str_);//复制字符串
	}
	void drawbutton()//画出按键
	{
		setfillcolor(color);//设置填充的颜色为按键的颜色
		settextstyle(35, 0, "宋体");//设置字体属性，宽度35，高度0（自适应）
		setlinecolor(BLACK);//设置边框线条颜色
		settextcolor(BLACK);//设置字体颜色
		setbkmode(TRANSPARENT);//设置字体背景为透明treansparent
		fillrectangle(x, y, x + width, y + height);//填充出一个矩形，参数为该矩形的左上和右下的坐标，颜色为上面所设置的颜色默认为黑色
		outtextxy(x + 5, y + 5, str);//在x+5,y+5位置输出设置好的字体文字str
	}
	//鼠标交互的一部分
	bool mouseInButton(MOUSEMSG m)//用于判断鼠标是否在按键的范围内
	{
		//m.x,m.y表示该鼠标的横纵坐标
		if (m.x >= x && m.x <= x + width && m.y >= y && m.y <= y + height)
		{
			color = RED;//如果在就将按键颜色改变
			return true;
		}
		else
		{
			color = YELLOW;//变回来
			return false;
		}
	}
	~button() {//析构函数
		delete[]str;
	}
};
int i = 0;
int j = 0;
int main()
{       PlaySound(TEXT("背景音乐2.mp3"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int n;//参加人数
	SetWindowText(GetHWnd(), "博饼");
	initgraph(360, 760);//初始化一个图形窗口
	IMAGE zz = 0;//
	IMAGE mm = 0;//
	IMAGE nn = 0;//定义一个图形变量并初始化
	IMAGE ww = 0;//碗
	IMAGE img[64];
	IMAGE tz1, tz2, tz3, tz4, tz5, tz6;
	loadimage(&tz1, "01.png", 48, 48);
	loadimage(&tz2, "02.png", 48, 48);
	loadimage(&tz3, "03.png", 48, 48);
	loadimage(&tz4, "04.png", 48, 48);
	loadimage(&tz5, "05.png", 48, 48);
	loadimage(&tz6, "06.png", 48, 48);
	for (int i = 1; i <= 64; i++) {
		char filename[64] = "";
		sprintf(filename, "%d.png", i);
		loadimage(&img[i - 1], filename, 360, 330);
	}
	//加载摇色子动画
menu:
	loadimage(&mm, "photo.png", 360, 760);
	putimage(0, 0, &mm);
	button b1, b2,b3;
	b1.build(105, 250, 150, 50, YELLOW, "开始游戏");
	b1.drawbutton();//将按键画出
	b2.build(105, 330, 150, 50, YELLOW, "游戏规则");
	b2.drawbutton();
	b3.build(105, 410, 150, 50, YELLOW, "游戏奖品");
	b3.drawbutton();
	while (1)
	{
		//更新按键，对按键进行重新绘制
		b1.drawbutton();
		b2.drawbutton();
		b3.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//当鼠标在按键的范围内且左键按下，WM_LBUTTONDOWN----window message left button down
		{
			goto index;
		}
		else if (b2.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)
		{
			goto rule;
		}
		else if (b3.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)
		{
			goto prize;
		}
	}//主菜单
index:
	b1.build(0, 0, 0, 0, YELLOW, "");
	b1.drawbutton();
	b2.build(0, 0, 0, 0, YELLOW, "");
	b2.drawbutton();
	loadimage(&mm, "photo.png", 360, 760);
	putimage(0, 0, &mm);//消除按键
	settextstyle(16, 0, "黑体");
	settextcolor(WHITE);
	outtextxy(100, 305, "请输入参加人数后回车");
	scanf("%d", &n);
	struct play {
		int numb; //玩家序号 
		int a[6]; //色子点数
		int A[6];//色子计数器 
		char x[10];//中奖类型（级别）		 
	}player[1000];//定义玩家信息
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 6; j++) {
			player[i].A[j] = 0;
		}
	}
	for ( i = 0; i < n; i++) {
		for ( j = 0; j < 6; j++) {
			player[i].a[j] = rand() % 5 + 1;//随机色子赋值
		}
		for ( j = 0; j < 6; j++) {
			player[i].A[player[i].a[j] - 1]++;
		}
		//色子计数器计数 
		if (player[i].A[3] == 4 && player[i].A[1] == 2)
			strcpy(player[i].x, "插金花");
		else if (player[i].A[3] == 6)
			strcpy(player[i].x, "六红勃");
		else if (player[i].A[0] == 6)
			strcpy(player[i].x, "遍地锦");
		else if (player[i].A[1] == 6)
			strcpy(player[i].x, "黑六勃");
		else if (player[i].A[3] == 5)
			strcpy(player[i].x, "五红");
		else if (player[i].A[1] == 5)
			strcpy(player[i].x, "五子登科");
		else if (player[i].A[3] == 4)
			strcpy(player[i].x, "四红");
		else if (player[i].A[0] == 1 && player[i].A[1] == 1 && player[i].A[2] == 1 && player[i].A[3] == 1 && player[i].A[4] == 1 && player[i].A[5] == 1)
			strcpy(player[i].x, "对堂");
		else if (player[i].A[3] == 3)
			strcpy(player[i].x, "三红");
		else if (player[i].A[0] == 4)
			strcpy(player[i].x, "四进");
		else if (player[i].A[3] == 2)
			strcpy(player[i].x, "二举");
		else if (player[i].A[3] == 1)
			strcpy(player[i].x, "一秀");
		else strcpy(player[i].x, "无");
	}
	
	loadimage(&ww, "碗.png", 360, 330);
	putimage(0, 0, &ww);//加载碗
	setfillcolor(RED);
	fillrectangle(5, 360, 355, 760);
	outtextxy(160, 340, "记录");
	for (int i = 1; i <= n; i++) {
		char str[10];
		sprintf(str, "%d", i);
		outtextxy(8, 358 + i * 25, str);
		outtextxy(10, 358 + i * 25, " 号玩家获得了  ");
	}
	b1.build(120, 280, 110, 40, YELLOW, "摇骰子");
	b1.drawbutton();//将按键画出
	i = 0;
	while (i<n) {
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();

		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//当鼠标在按键的范围内且左键按下
		{

			int count = 0;
			while (count <= 64) {
				putimage(0, 0, &img[count++]);
				Sleep(33);
				count++;//色子动画
			}

			for (int j = 0; j < 6; j++) {
				switch (player[i].a[j]) {
				case 1:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz1);
					break;
				case 2:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz2);
					break;
				case 3:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz3);
					break;
				case 4:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz4);
					break;
				case 5:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz5);
					break;
				case 6:
					putimage(105 + j % 3 * 50, 120 + (j / 3) * 50, &tz6);
				}
			}
			settextstyle(18, 0, "黑体");
			settextcolor(WHITE);
			
			outtextxy(130, 383 + i * 25, player[i].x);//输出玩家获奖类型
			//显示色子
			i++;
		}
		if (i == n) {
			while (1) {
				b1.build(105, 280, 147, 40, YELLOW, "再来一轮");
				b2.build(105, 230, 147, 40, YELLOW, "返回菜单");
				b1.drawbutton();
				b2.drawbutton();
				MOUSEMSG m = GetMouseMsg();
				if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//当鼠标在按键的范围内且左键按下，WM_LBUTTONDOWN----window message left button down
				{
					i = 0;
					goto index;
				}
				else if (b2.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)
				{
					i = 0;
					goto menu;
				}
			}
		}
	}
rule:
	b1.build(0, 0, 100, 40, YELLOW, "返回");
	b1.drawbutton();
	loadimage(&nn, "规则4.jpg", 360, 760);
	putimage(0, 0, &nn);
	while (1)
	{
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//当鼠标在按键的范围内且左键按下，WM_LBUTTONDOWN----window message left button down
		{
			goto menu;
		}
	}
	closegraph();//关闭图像
	return 0;
prize:
	b1.build(0, 0, 100, 40, YELLOW, "返回");
	b1.drawbutton();
	loadimage(&nn, "奖品.png", 360, 760);
	putimage(0, 0, &nn);
	while (1)
	{
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//当鼠标在按键的范围内且左键按下，WM_LBUTTONDOWN----window message left button down
		{
			goto menu;
		}
	}
	closegraph();//关闭图像
	return 0;
}

