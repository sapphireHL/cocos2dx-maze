#pragma once
#include "MazeGenerator.h"
#include "point.h"
#include <time.h>

//recursive division
class MazeGeneratorRD : public MazeGenerator
{
public:
	MazeGeneratorRD();
	~MazeGeneratorRD();
	void generate();

private:
	void init();
	void recursive(point leftup, point rightbottom);
	void openDoor(point a, point b);
};

