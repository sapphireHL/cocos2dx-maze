#pragma once
#include "point.h"
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

class MazeSolver
{
public:
	MazeSolver();
	~MazeSolver();
	virtual void solve(const vector<vector<int>>& map);
	void showPath();
	vector<point> getPath();

private:
	void gotoXY(int x, int y);

protected:
	vector<point> path;
};

