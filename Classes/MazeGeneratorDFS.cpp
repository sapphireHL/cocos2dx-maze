#include "MazeGeneratorDFS.h"



MazeGeneratorDFS::MazeGeneratorDFS()
{
}


MazeGeneratorDFS::~MazeGeneratorDFS()
{
}

void MazeGeneratorDFS::generate()
{
	init();
	if (rows == 0 || cols == 0)
		return;
	srand((unsigned int)time(NULL));

	stack<point> stk;//路的列表
	vector<vector<int>> visited(rows, vector<int>(cols));

	stk.push(point(1, 1));//加入起点

	while (!stk.empty()) {
		point cur = stk.top();
		visited[cur.x][cur.y] = 1;

		//找到未访问的邻近点
		vector<int> validDirection = getValidDirection(cur, visited);
		//将这两个路之前的墙打通,将该点入栈
		if (!validDirection.empty()) {
			int nextDir = getRandomDirection(validDirection);
			point next(cur);
			switch (nextDir) {
			case UP:
				next.x -= 2;
				map[cur.x - 1][cur.y] = 1;
				break;
			case DOWN:
				next.x += 2;
				map[cur.x + 1][cur.y] = 1;
				break;
			case LEFT:
				next.y -= 2;
				map[cur.x][cur.y - 1] = 1;
				break;
			case RIGHT:
				next.y += 2;
				map[cur.x][cur.y + 1] = 1;
				break;
			default:
				break;
			}
			stk.push(next);
		}
		//若邻近点全访问过，则出栈
		else {
			stk.pop();
		}
	}
}

void MazeGeneratorDFS::init()
{
	for (int i = 1; i < rows - 1; i += 2) {
		for (int j = 1; j < cols - 1; j += 2) {
			map[i][j] = 1;
		}
	}
}

vector<int> MazeGeneratorDFS::getValidDirection(point cur, vector<vector<int>>& visited)
{
	vector<int> validDirection;
	int dir[4][2] = { { -2,0 },{ 2,0 },{ 0,-2 },{ 0,2 } };
	for (int i = 0; i < 4; i++) {
		point next(cur.x + dir[i][0], cur.y + dir[i][1]);
		if (valid(next) && !visited[next.x][next.y]) {
			validDirection.push_back(i);
		}
	}
	return validDirection;
}

bool MazeGeneratorDFS::valid(point cur)
{
	if (cur.x < 0 || cur.x >= rows || cur.y < 0 || cur.y >= cols)
		return false;
	return true;
}

int MazeGeneratorDFS::getRandomDirection(vector<int>& dir)
{
	if (dir.empty())
		return -1;
	int index = rand() % dir.size();
	return dir[index];
}
