#pragma once
class point
{
public:
	point();
	point(int xx, int yy);
	point(const point& a);
	~point();
	friend bool operator ==(const point& a, const point& b);

public:
	int x, y;
};

