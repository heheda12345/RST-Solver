#include<stdlib.h>

#include "point.h"

namespace RECTILINEAR_STEINER_TREE {
int Point::dist(const Point &b)const
{
	return abs(x - b.x) + abs(y - b.y);
}

int dist(const Point &a, const Point &b)
{
	return a.dist(b);
}

std::ostream &operator << (std::ostream &out, const Point &a)
{
	using namespace std;
	out << a.x << " " << a.y << " ";
	return out;
}

std::istream &operator >> (std::istream &in, Point &a)
{
	using namespace std;
	in >> a.x >> a.y;
	return in;
}

}
