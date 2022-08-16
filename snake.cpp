#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define SNAKE_NUM 500
struct Snake
{
	int size;//蛇的节
	int dir;//蛇的方向 
	int speed;//移动速度
	POINT coor[SNAKE_NUM];//坐标
}snake;  
struct Food
{
	int x;
	int y;
	int r;
	int flag;
	DWORD color;
}food;
enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//数据初始化
void GameInit()
{	//初始化窗口及数据
	initgraph(640, 480);
	snake.size = 3;
	snake.speed = 10;
	snake.dir=RIGHT;
	for (int i = snake.size ;i > 0;i--)
	{
		snake.coor[i].x = 50-10*i;
		snake.coor[i].y = 10;
	}
	srand(GetTickCount());
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
	food.r = 10;
	food.flag = 1;

}
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(93, 107, 153));
	cleardevice();
	for (int i = snake.size ;i > 0;i--)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		setfillcolor(food.color);
		solidcircle(food.x, food.y, food.r);
		setfillcolor(RGB(255, 255, 255));
	}
	EndBatchDraw();
}
//蛇的移动
void Snake_move()
{
	for (int i = snake.size ;i > 0;i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+= snake.speed;
		if (snake.coor[0].y >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-= snake.speed;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x+= snake.speed;
		if (snake.coor[0].x >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	}
	
}
//按键介入控制方向
void Control()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case'72':
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case'80':		
			if (snake.dir != UP)
		{
			snake.dir = DOWN;
		}
			break;
		case 'a':
		case 'A':
		case'75':
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case'77':
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case ' ':
			while (1)
				if (_getch() == ' ')
					return;
			break;
		}
	}
}
//食物生成
void EatFood()
{
	if (food.flag==1&&snake.coor[0].x >=food.x-food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y <= food.y + food.r && snake.coor[0].y >= food.y-food.r)
	{
		food.flag = 0;
		snake.size++;
	}
	if (!food.flag)
	{
		srand(GetTickCount());
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color =RGB(rand() % 255, rand() % 255, rand() % 255);
		food.r = 10;
		food.flag = 1;
	}
}
int main()
{
	GameInit();
	GameDraw();
	while (1)
	{
		GameDraw();
		Snake_move();
		Control();
		Sleep(65);
		EatFood();
	}
	return 0;
}