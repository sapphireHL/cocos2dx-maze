#pragma once
#include "MazeGenerator.h"
#include "point.h"
#include <time.h>
#include <stack>

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

class MazeGeneratorDFS : public MazeGenerator
{
public:
	MazeGeneratorDFS();
	~MazeGeneratorDFS();
	void generate();

private:
	void init();
	vector<int> getValidDirection(point cur, vector<vector<int>>& visited);
	bool valid(point cur);
	int getRandomDirection(vector<int> &dir);
};

