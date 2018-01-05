#include "MazeSolverAStar.h"



MazeSolverAStar::MazeSolverAStar()
{
}


MazeSolverAStar::~MazeSolverAStar()
{
	if(start)
		delete start;
	if(end)
		delete end;
	for (int i = 0; i < (int)memoryCollector.size(); i++)
		if(memoryCollector[i])
			delete memoryCollector[i];
}

void MazeSolverAStar::solve(const vector<vector<int>>& map)
{
	init(map);

	bool isFindGoal = false;
	while (!minheap.empty()) {
		//取出代价最小的
		Node* cur = minheap.top();
		minheap.pop();
		close_list[cur->pos.x][cur->pos.y] = 1;
		//检查相邻四个格子
		auto surroundingNodes = getSurroundingNodes(cur);
		for (auto node: surroundingNodes) {
			//找到终点
			if (*node == *end) {
				isFindGoal = true;
				end->parent = cur;
				break;
			}
			//若格子不在openlist，加入
			if (!open_list[node->pos.x][node->pos.y]) {
				open_list[node->pos.x][node->pos.y] = 1;
				calcG(node, cur);
				calcH(node);
				calcF(node);
				node->parent = cur;
				minheap.push(node);
			}
			//若已经在openlist，检查是否更优
			else {
				int newg = cur->g + 1;
				if (newg < node->g) {
					node->g = newg;
					calcF(node);
					node->parent = cur;
				}
			}
		}
		if (isFindGoal) {
			pathTrack();
			break;
		}
	}
}

void MazeSolverAStar::init(const vector<vector<int>>& map)
{
	if (map.empty())
		return;
	this->map = map;
	int rows = map.size(), cols = map[0].size();
	start = new Node(1, 1);
	end = new Node(rows - 2, cols - 2);

	open_list.resize(rows, vector<int>(cols));
	close_list.resize(rows, vector<int>(cols));
	open_list[start->pos.x][start->pos.y] = 1;
	minheap.push(start);
}

bool MazeSolverAStar::valid(Node * cur)
{
	int rows = map.size(), cols = map[0].size();
	//超出边界
	if (cur->pos.x < 0 || cur->pos.x >= rows || cur->pos.y < 0 || cur->pos.y >= cols)
		return false;
	//墙
	if (map[cur->pos.x][cur->pos.y] == 0)
		return false;
	//访问过
	if (close_list[cur->pos.x][cur->pos.y])
		return false;
	return true;
}

vector<Node*> MazeSolverAStar::getSurroundingNodes(Node * cur)
{
	vector<Node*> nodes;
	int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
	for (int i = 0; i < 4; i++) {
		Node* neighbor = new Node(cur->pos.x + dir[i][0], cur->pos.y + dir[i][1]);
		memoryCollector.push_back(neighbor);
		if (valid(neighbor))
			nodes.push_back(neighbor);
	}
	return nodes;
}

void MazeSolverAStar::pathTrack()
{
	Node* p = end;
	while (p) {
		path.push_back(p->pos);
		p = p->parent;
	}
	reverse(path.begin(), path.end());
}

void MazeSolverAStar::calcF(Node * cur)
{
	cur->f = cur->g + cur->h;
}

void MazeSolverAStar::calcG(Node * cur, Node* pre)
{
	cur->g = pre->g + 1;
}

void MazeSolverAStar::calcH(Node * cur)
{
	cur->h = abs(cur->pos.x - end->pos.x) + abs(cur->pos.y - end->pos.y);
}
