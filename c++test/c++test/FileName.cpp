	#include<iostream>
	#include<graphics.h>
	#include <cmath>
	#include<stdlib.h>
	#include<time.h>
	#include<Windows.h>
	using namespace std;
	#define PI 3.141
	#define height 680
	#define width  740
	#define motherx 340
	#define mothery 370
	#define e 2.71828
	IMAGE image[12];
	struct Point
	{
		double x;
		double y;
		COLORREF color;
	}point[15][628];
	struct interpoint
	{
		double x;
		double y;
		COLORREF color;
	}interpoint[60];
	struct outerpoint
	{
		double x;
		double y;
		COLORREF color;
	}outerpoint[60];
	COLORREF color[11] = { RGB(25, 120,130),RGB(252,222,250),RGB(55,132,83),RGB(25,230,40),RGB(25,24,112),RGB(255,0,0) ,RGB(153, 102, 255)
	,RGB(255,125,0),RGB(75,0,130),RGB(102,0,204),RGB(239,108,234)
	};

	struct Distance
	{
		double distance;
	}mdis[15][628];
	void initsetpoint()//第一圈的点
	{
		int b = rand() % 11;
		int i = 0;
		for (double t = 0; t <= 2 * PI; t += 0.01)//第一次画
		{
			point[0][i].x = 10 * (16 * pow(sin(t), 3))+ motherx;
			point[0][i].y = -(10 * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t))) +mothery;
			i++;
			point[0][i].color = color[b];
		}

	}
	void initsetdistance()
		{
			int i = 0;
			for (i = 0; i < 628; i++)
			{
				mdis[0][i].distance = sqrt(pow(point[0][i].x - motherx, 2) + pow(point[0][i].y - mothery, 2));
			}
		}
	void initalldistance()
	{
		for (int n = 0; n < 15; n++)
		{
			for (int a = 0; a < 628; a++)
			{
				mdis[n][a].distance = sqrt(pow(point[n][a].x - motherx, 2) + pow(point[n][a].y - mothery, 2));
			}
		}
	}
	void draw()
		{   
		//double sussess = 1 / (1 + pow(e, 1.5- factor));//factor 越大，成功的越大
		for (int n = 0; n < 15; n++)
		{
			for (int i = 0; i < 628; i++)
			{
				putpixel(point[n][i].x, point[n][i].y, point[n][i].color);
			
			}
		}
		}
	void initchangepoint()
	{
		double factor;
		for (factor = 1; factor <= 1.3; factor += 0.02)//初始形状的心形
		{
			int i = 0;
			double newdis;
			static int count = 0;
			for (i = 0; i < 628; i++)
			{
				double cos1 = (point[0][i].x - motherx) / mdis[0][i].distance;
				double sin1 = (point[0][i].y - mothery) / mdis[0][i].distance;
				newdis = mdis[0][i].distance * factor;
				point[count][i].x = motherx + newdis * cos1;
				point[count][i].y = mothery + newdis * sin1;
				point[count][i].color = color[rand() % 11];
			}
			count++;
		}
	}
	void setinnerpoint()
	{
		int n = 60;
		int a;
		while (n--)
		{
			a = rand() % 10;
			int x = rand() % 160 + motherx;
			int y = rand() % 125 + mothery;
			double dis = sqrt(pow(point[0][1].x -x, 2) + pow(point[0][1].y - y, 2));
			double success = 10 / (2 + (int)dis/10);
			if (a < success)
			{
				solidcircle(x,y,4);
			}
		}
	}
	
	int main()
	{
		IMAGE image[10];
		srand((unsigned int)time(NULL));
		int a = rand() % 100;
		initgraph(width,height);
		initsetpoint();
		initsetdistance();
		initchangepoint();
		initalldistance();
		draw();
		int count = 0;
		//我用二维数组来找到每一圈上的所有点，实现缩放时只需要改变所有点的坐标就可以
		while (true)
		{
			for (double factor = 1; factor <= 1.01; factor += 0.001)
			{
				/*Resize(&image[count], 740, 680);
				SetWorkingImage(&image[count]);*/
				for (int n = 0; n < 15; n++)
				{
					double newdis = 0;
					for (int a = 0; a < 628; a++)
					{
						double cos1 = (point[n][a].x - motherx) / mdis[n][a].distance;
						double sin1 = (point[n][a].y - mothery) / mdis[n][a].distance;
						newdis = mdis[n][a].distance * factor;
						point[n][a].x = motherx + newdis * cos1;
						point[n][a].y = mothery + newdis * sin1;
					}
				}
				count++;
				draw();
				Sleep(150);
				if (factor < 1.01)
				{
					cleardevice();
				}

			}
			for (double factor = 1; factor >= 0.99; factor -= 0.001)
			{
				for (int n = 0; n < 15; n++)
				{
					double newdis = 0;
					for (int a = 0; a < 628; a++)
					{
						double cos1 = (point[n][a].x - motherx) / mdis[n][a].distance;
						double sin1 = (point[n][a].y - mothery) / mdis[n][a].distance;
						newdis = mdis[n][a].distance * factor;
						point[n][a].x = motherx + newdis * cos1;
						point[n][a].y = mothery + newdis * sin1;
					}
				}
				count++;
				draw();
				Sleep(150);
				if (factor > 0.99)
				{
					cleardevice();
				}
			}
		}
		setinnerpoint();
		system("pause");
		return 0;
	}		