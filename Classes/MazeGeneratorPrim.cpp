#include "MazeGeneratorPrim.h"



MazeGeneratorPrim::MazeGeneratorPrim()
{
}



MazeGeneratorPrim::~MazeGeneratorPrim()
{
}

void MazeGeneratorPrim::init()
{
	//������·��ż����ǽ
	for (int i = 1; i < rows - 1; i += 2) {
		for (int j = 1; j < cols - 1; j += 2) {
			map[i][j] = 1;
		}
	}
}

point MazeGeneratorPrim::getRandomWall(const vector<point>& vec)
{
	if (vec.empty())
		return point();
	int index = rand() % vec.size();
	return vec[index];
}

void MazeGeneratorPrim::addSurroundingWallsToList(vector<point>& list, point road)
{
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
	for (int i = 0; i < 4; i++) {
		point wall(road.x + dir[i][0], road.y + dir[i][1]);
		if (wall.x <= 0 || wall.x >= rows - 1 || wall.y <= 0 || wall.y >= cols - 1)
			continue;
		list.push_back(wall);
	}
}

void MazeGeneratorPrim::generate()
{
	init();
	if (rows == 0 || cols == 0)
		return;
	srand(unsigned int(time(NULL)));

	vector<point> list;//δ����ǽ���б�
	vector<vector<int>> visited(rows, vector<int>(cols));

	//��������ǽ�����б�
	list.push_back(point(1, 2));
	list.push_back(point(2, 1));
	visited[1][1] = 1;

	while (!list.empty()) {
		point curWall = getRandomWall(list);
		point roadA, roadB;
		//�ָ����¸���
		if (curWall.x % 2 == 0) {
			roadA.x = curWall.x - 1;
			roadA.y = curWall.y;
			roadB.x = curWall.x + 1;
			roadB.y = curWall.y;
		}
		//�ָ����Ҹ���
		else if (curWall.y % 2 == 0) {
			roadA.x = curWall.x;
			roadA.y = curWall.y - 1;
			roadB.x = curWall.x;
			roadB.y = curWall.y + 1;
		}
		//���ֻ��һ�����ӱ����ʹ�����ͨǽ������һ�����ӵ�ǽ�����б�
		if (visited[roadA.x][roadA.y] + visited[roadB.x][roadB.y] == 1) {
			map[curWall.x][curWall.y] = 1;
			if (visited[roadA.x][roadA.y])
				addSurroundingWallsToList(list, roadB);
			else if (visited[roadB.x][roadB.y])
				addSurroundingWallsToList(list, roadA);
			visited[roadA.x][roadA.y] = visited[roadB.x][roadB.y] = 1;
		}

		//�б��Ƴ�ǽ
		list.erase(find(list.begin(), list.end(), curWall));
	}
}
