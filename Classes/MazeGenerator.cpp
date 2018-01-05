#include "MazeGenerator.h"



MazeGenerator::MazeGenerator()
{
}

MazeGenerator::MazeGenerator(int h, int w)
{
	rows = 2 * h + 1;
	cols = 2 * w + 1;
	map.resize(rows, vector<int>(cols));
}

void MazeGenerator::setSize(int h, int w)
{
	rows = 2 * h + 1;
	cols = 2 * w + 1;
	map.resize(rows, vector<int>(cols));
}


MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::generate()
{
}

void MazeGenerator::showMaze()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0)
				cout << "¡ö";
			else
				cout << "  ";
		}
		cout << endl;
	}
}

vector<vector<int>> MazeGenerator::getMap()
{
	return map;
}
