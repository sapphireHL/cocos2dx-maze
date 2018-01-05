#pragma once
#include "MazeGenerator.h"
#include "point.h"
#include <time.h>

class MazeGeneratorPrim : public  MazeGenerator
{
public:
	MazeGeneratorPrim();
	~MazeGeneratorPrim();
	void generate();

private:
	void init();
	point getRandomWall(const vector<point>& vec);
	void addSurroundingWallsToList(vector<point>& list, point road);
};

