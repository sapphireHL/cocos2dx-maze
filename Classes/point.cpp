#include "point.h"



point::point()
{
}

point::point(int xx, int yy)
{
	x = xx;
	y = yy;
}

point::point(const point & a)
{
	x = a.x;
	y = a.y;
}


point::~point()
{
}

bool operator==(const point & a, const point & b)
{
	return (b.x == a.x) && (b.y == a.y);
}
