#pragma once
#include <iostream>
#include <vector>

using namespace std;

class MazeGenerator
{
public:
	MazeGenerator();
	MazeGenerator(int h, int w);
	void setSize(int h, int w);
	~MazeGenerator();
	virtual void generate();
	void showMaze();
	vector<vector<int>> getMap();

protected:
	int rows;
	int cols;
	vector<vector<int>> map;
};

