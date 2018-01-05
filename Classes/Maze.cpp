#include "Maze.h"



Maze::Maze()
{
}

Maze::Maze(int h, int w)
{
	prim.setSize(h, w);
	dfs.setSize(h, w);
	rd.setSize(h, w);
}


Maze::~Maze()
{
}

//0:prim  1:dfs   2:recursive division
void Maze::generateMaze(int method)
{
	switch (method) {
	case 0:
		mg = &prim;
		break;
	case 1:
		mg = &dfs;
		break;
	case 2:
		mg = &rd;
		break;
	default:
		return;
	}

	mg->generate();
	mg->showMaze();
}

void Maze::solveMaze()
{
	if (mg) {
		auto map = mg->getMap();
		if (!map.empty()) {
			ms = &astar;
			ms->solve(map);
			ms->showPath();
		}
	}
}

vector<vector<int>> Maze::getMazeMap()
{
	if (mg) {
		return mg->getMap();
	}
	return vector<vector<int>>();
}

vector<point> Maze::getPath()
{
	if (ms) {
		return ms->getPath();
	}
	return vector<point>();
}
