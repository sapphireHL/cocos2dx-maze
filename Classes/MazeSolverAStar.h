#pragma once
#include "MazeSolver.h"
#include "point.h"
#include "queue"
#include <functional>

struct Node
{
	point pos;
	int f, g, h;//f=g+h, g:起点到当前点的代价，h:终点到当前点的代价
	Node *parent;//父节点
	Node(int xx = 0, int yy = 0) :pos(point(xx, yy)), f(0), g(0), h(0), parent(NULL) {};
	friend bool operator >(const Node& a, const Node& b) {
		return a.f > b.f;
	}
	friend bool operator ==(const Node& a, const Node& b) {
		return a.pos == b.pos;
	}
};



class MazeSolverAStar : public MazeSolver
{
public:
	MazeSolverAStar();
	~MazeSolverAStar();
	void solve(const vector<vector<int>>& map);

private:
	void init(const vector<vector<int>>& map);
	bool valid(Node* cur);
	vector<Node*> getSurroundingNodes(Node* cur);
	void pathTrack();
	void calcF(Node* cur);
	void calcG(Node* cur, Node* pre);
	void calcH(Node* cur);

private:
	vector<vector<int>> map;
	priority_queue<Node*, vector<Node*>, greater<Node*>> minheap;//open list
	vector<vector<int>> open_list;
	vector<vector<int>> close_list;
	vector<Node*> memoryCollector;
	Node *start, *end;
};

