#include "MazeGeneratorRD.h"



MazeGeneratorRD::MazeGeneratorRD()
{
}

MazeGeneratorRD::~MazeGeneratorRD()
{
}

void MazeGeneratorRD::generate()
{
	init();
	if (rows == 0 || cols == 0)
		return;
	srand((unsigned int)time(NULL));

	//递归分割
	point leftup(1, 1), rightbottom(rows - 2, cols - 2);
	recursive(leftup, rightbottom);
}

void MazeGeneratorRD::init()
{
	//让迷宫全是路，递归加墙
	for (int i = 1; i < rows - 1; i++) {
		for (int j = 1; j < cols - 1; j++) {
			map[i][j] = 1;
		}
	}
}

void MazeGeneratorRD::recursive(point leftup, point rightbottom)
{
	int height = rightbottom.x - leftup.x + 1, width = rightbottom.y - leftup.y + 1;
	//终止条件
	if (height <= 2 || width <= 2)
		return;

	//在偶数行随机画墙
	int xpos = leftup.x + 1 + rand() % (height / 2) * 2, ypos = leftup.y + 1 + rand() % (width / 2) * 2;
	for (int i = leftup.x; i <= rightbottom.x; i++)
		map[i][ypos] = 0;
	for (int j = leftup.y; j <= rightbottom.y; j++)
		map[xpos][j] = 0;

	//随机在三面墙上开门,奇数行，左侧为0，顺时针转
	int notopen = rand() % 4;
	switch (notopen) {
	case 0:
		openDoor(point(leftup.x, ypos), point(xpos - 1, ypos));//2
		openDoor(point(xpos, ypos + 1), point(xpos, rightbottom.y));//3
		openDoor(point(xpos + 1, ypos), point(rightbottom.x, ypos));//4
		break;
	case 1:
		openDoor(point(xpos, leftup.y), point(xpos, ypos - 1));//1
		openDoor(point(xpos, ypos + 1), point(xpos, rightbottom.y));//3
		openDoor(point(xpos + 1, ypos), point(rightbottom.x, ypos));//4
		break;
	case 2:
		openDoor(point(xpos, leftup.y), point(xpos, ypos - 1));//1
		openDoor(point(leftup.x, ypos), point(xpos - 1, ypos));//2
		openDoor(point(xpos + 1, ypos), point(rightbottom.x, ypos));//4
		break;
	case 3:
		openDoor(point(xpos, leftup.y), point(xpos, ypos - 1));//1
		openDoor(point(leftup.x, ypos), point(xpos - 1, ypos));//2
		openDoor(point(xpos, ypos + 1), point(xpos, rightbottom.y));//3
		break;
	default:
		break;
	}

	//递归左上角区域
	recursive(leftup, point(xpos - 1, ypos - 1));
	//右上角
	recursive(point(leftup.x, ypos + 1), point(xpos - 1, rightbottom.y));
	//左下角
	recursive(point(xpos + 1, leftup.y), point(rightbottom.x, ypos - 1));
	//右下角
	recursive(point(xpos + 1, ypos + 1), rightbottom);
}

//在一条线上随机开门
void MazeGeneratorRD::openDoor(point a, point b)
{
	//横,奇数行开门
	if (a.x == b.x) {
		int doorPos = a.y + rand() % ((b.y - a.y) / 2 + 1) * 2;
		map[a.x][doorPos] = 1;
	}
	//竖
	else if (a.y == b.y) {
		int doorPos = a.x + rand() % ((b.x - a.x) / 2 + 1) * 2;
		map[doorPos][a.y] = 1;
	}
}
