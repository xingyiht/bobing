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
#pragma warning(disable:4996)
using namespace std;
class button
{
public:
	int x;
	int y;//(x,y)�������Ͻǵ�λ��
	int width;//�������
	int height;//�����߶�
	COLORREF color;//��������ɫ����ɫȫ�����Ǵ�д��Ӣ�ĵ���
	char* str;//�����ϵ���
	void build(int x_, int y_, int width_, int height_, COLORREF color_, const char* str_) //�԰������г�ʼ��������Ҳ����ֱ���ù��캯��
	{
		x = x_;
		y = y_;
		width = width_;
		height = height_;
		color = color_;
		str = new char[strlen(str_) + 1];//�ַ�ָ����ҪԤ�ȷ����ڴ�
		strcpy(str, str_);//�����ַ���
	}
	void drawbutton()//��������
	{
		setfillcolor(color);//����������ɫΪ��������ɫ
		settextstyle(35, 0, "����");//�����������ԣ����35���߶�0������Ӧ��
		setlinecolor(BLACK);//���ñ߿�������ɫ
		settextcolor(BLACK);//����������ɫ
		setbkmode(TRANSPARENT);//�������屳��Ϊ͸��treansparent
		fillrectangle(x, y, x + width, y + height);//����һ�����Σ�����Ϊ�þ��ε����Ϻ����µ����꣬��ɫΪ���������õ���ɫĬ��Ϊ��ɫ
		outtextxy(x + 5, y + 5, str);//��x+5,y+5λ��������úõ���������str
	}
	//��꽻����һ����
	bool mouseInButton(MOUSEMSG m)//�����ж�����Ƿ��ڰ����ķ�Χ��
	{
		//m.x,m.y��ʾ�����ĺ�������
		if (m.x >= x && m.x <= x + width && m.y >= y && m.y <= y + height)
		{
			color = RED;//����ھͽ�������ɫ�ı�
			return true;
		}
		else
		{
			color = YELLOW;//�����
			return false;
		}
	}
	~button() {//��������
		delete[]str;
	}
};
int i = 0;
int j = 0;
int main()
{
	int n;//�μ�����
	SetWindowText(GetHWnd(), "����");
	initgraph(360, 760);//��ʼ��һ��ͼ�δ���
	IMAGE zz = 0;//
	IMAGE mm = 0;//
	IMAGE nn = 0;//����һ��ͼ�α�������ʼ��
	IMAGE ww = 0;//��
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
	//����ҡɫ�Ӷ���
menu:
	loadimage(&mm, "photo.png", 360, 760);
	putimage(0, 0, &mm);
	button b1, b2,b3;
	b1.build(105, 250, 150, 50, YELLOW, "��ʼ��Ϸ");
	b1.drawbutton();//����������
	b2.build(105, 330, 150, 50, YELLOW, "��Ϸ����");
	b2.drawbutton();
	b3.build(105, 410, 150, 50, YELLOW, "��Ϸ��Ʒ");
	b3.drawbutton();
	while (1)
	{
		//���°������԰����������»���
		b1.drawbutton();
		b2.drawbutton();
		b3.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//������ڰ����ķ�Χ����������£�WM_LBUTTONDOWN----window message left button down
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
	}//���˵�
index:
	b1.build(0, 0, 0, 0, YELLOW, "");
	b1.drawbutton();
	b2.build(0, 0, 0, 0, YELLOW, "");
	b2.drawbutton();
	loadimage(&mm, "photo.png", 360, 760);
	putimage(0, 0, &mm);//��������
	settextstyle(16, 0, "����");
	settextcolor(WHITE);
	outtextxy(100, 305, "������μ�������س�");
	scanf("%d", &n);
	struct play {
		int numb; //������ 
		int a[6]; //ɫ�ӵ���
		int A[6];//ɫ�Ӽ����� 
		char x[10];//�н����ͣ�����		 
	}player[1000];//���������Ϣ
	for (i = 0; i < 1000; i++) {
		for (j = 0; j < 6; j++) {
			player[i].A[j] = 0;
		}
	}
	for ( i = 0; i < n; i++) {
		for ( j = 0; j < 6; j++) {
			player[i].a[j] = rand() % 5 + 1;//���ɫ�Ӹ�ֵ
		}
		for ( j = 0; j < 6; j++) {
			player[i].A[player[i].a[j] - 1]++;
		}
		//ɫ�Ӽ��������� 
		if (player[i].A[3] == 4 && player[i].A[1] == 2)
			strcpy(player[i].x, "���");
		else if (player[i].A[3] == 6)
			strcpy(player[i].x, "���첪");
		else if (player[i].A[0] == 6)
			strcpy(player[i].x, "��ؽ�");
		else if (player[i].A[1] == 6)
			strcpy(player[i].x, "������");
		else if (player[i].A[3] == 5)
			strcpy(player[i].x, "���");
		else if (player[i].A[1] == 5)
			strcpy(player[i].x, "���ӵǿ�");
		else if (player[i].A[3] == 4)
			strcpy(player[i].x, "�ĺ�");
		else if (player[i].A[0] == 1 && player[i].A[1] == 1 && player[i].A[2] == 1 && player[i].A[3] == 1 && player[i].A[4] == 1 && player[i].A[5] == 1)
			strcpy(player[i].x, "����");
		else if (player[i].A[3] == 3)
			strcpy(player[i].x, "����");
		else if (player[i].A[0] == 4)
			strcpy(player[i].x, "�Ľ�");
		else if (player[i].A[3] == 2)
			strcpy(player[i].x, "����");
		else if (player[i].A[3] == 1)
			strcpy(player[i].x, "һ��");
		else strcpy(player[i].x, "��");
	}
	

	loadimage(&ww, "��.png", 360, 330);
	putimage(0, 0, &ww);//������
	setfillcolor(RED);
	fillrectangle(5, 360, 355, 760);
	outtextxy(160, 340, "��¼");
	for (int i = 1; i <= n; i++) {
		char str[10];
		sprintf(str, "%d", i);
		outtextxy(8, 358 + i * 25, str);
		outtextxy(10, 358 + i * 25, " ����һ����  ");

	}
	b1.build(120, 280, 110, 40, YELLOW, "ҡ����");
	b1.drawbutton();//����������
	i = 0;
	while (i<n) {
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();

		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//������ڰ����ķ�Χ�����������
		{

			int count = 0;
			while (count <= 64) {
				putimage(0, 0, &img[count++]);
				Sleep(33);
				count++;//ɫ�Ӷ���
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
			settextstyle(18, 0, "����");
			settextcolor(WHITE);
			
			outtextxy(130, 383 + i * 25, player[i].x);//�����һ�����
			//��ʾɫ��
			i++;
		}
		if (i == n) {
			while (1) {
				b1.build(105, 280, 147, 40, YELLOW, "����һ��");
				b2.build(105, 230, 147, 40, YELLOW, "���ز˵�");
				b1.drawbutton();
				b2.drawbutton();
				MOUSEMSG m = GetMouseMsg();
				if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//������ڰ����ķ�Χ����������£�WM_LBUTTONDOWN----window message left button down
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
	b1.build(0, 0, 100, 40, YELLOW, "����");
	b1.drawbutton();
	loadimage(&nn, "����4.jpg", 360, 760);
	putimage(0, 0, &nn);
	while (1)
	{
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//������ڰ����ķ�Χ����������£�WM_LBUTTONDOWN----window message left button down
		{
			goto menu;
		}
	}
	closegraph();//�ر�ͼ��
	return 0;
prize:
	b1.build(0, 0, 100, 40, YELLOW, "����");
	b1.drawbutton();
	loadimage(&nn, "��Ʒ.png", 360, 760);
	putimage(0, 0, &nn);
	while (1)
	{
		b1.drawbutton();
		MOUSEMSG m = GetMouseMsg();
		if (b1.mouseInButton(m) && m.uMsg == WM_LBUTTONDOWN)//������ڰ����ķ�Χ����������£�WM_LBUTTONDOWN----window message left button down
		{
			goto menu;
		}
	}
	closegraph();//�ر�ͼ��
	return 0;
}

