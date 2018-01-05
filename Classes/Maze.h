#pragma once

#include "MazeGeneratorDFS.h"
#include "MazeGeneratorPrim.h"
#include "MazeGeneratorRD.h"
#include "MazeSolverAStar.h"


class Maze
{
public:
	Maze();
	Maze(int h, int w);
	~Maze();
	void generateMaze(int method = 0);
	void solveMaze();
	vector<vector<int>> getMazeMap();
	vector<point> getPath();

private:
	MazeGeneratorDFS dfs;
	MazeGeneratorPrim prim;
	MazeGeneratorRD rd;
	MazeGenerator* mg;
	MazeSolverAStar astar;
	MazeSolver* ms;
};

