#include "MazeSolver.h"



MazeSolver::MazeSolver()
{
}


MazeSolver::~MazeSolver()
{
}

void MazeSolver::solve(const vector<vector<int>>& map)
{
}

void MazeSolver::showPath()
{
	for (int i = 0; i < (int)path.size(); i++) {
		Sleep(50);
		gotoXY(path[i].y * 2, path[i].x);
		cout << "��";
	}
}

vector<point> MazeSolver::getPath()
{
	return path;
}

void MazeSolver::gotoXY(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	/*COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��
	typedef struct _COORD {
	SHORT X; // horizontal coordinate
	SHORT Y; // vertical coordinate
	} COORD;*/
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
