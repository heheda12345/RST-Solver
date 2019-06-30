#ifndef __POINT_H__
#define __POINT_H__

#include <ostream>
#include <istream>

namespace RECTILINEAR_STEINER_TREE {
class Point
{
public:
	Point(const int &_ = 0, const int &__ = 0): x(_), y(__) {}
	int dist(const Point &)const;
	friend int dist(const Point &, const Point &);
	friend Point operator + (const Point &a, const Point &b) {return Point(a.x + b.x, a.y + b.y);}
	friend Point operator - (const Point &a, const Point &b) {return Point(a.x - b.x, a.y - b.y);}
	friend bool operator < (const Point &a, const Point &b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
	friend bool operator == (const Point &a, const Point &b) {return a.x == b.x && a.y == b.y;}
	friend int cross(const Point &a, const Point &b) {return a.x * b.y - a.y * b.x;}
	friend std::ostream & operator << (std::ostream &out, const Point &);
	friend std::istream & operator >> (std::istream &in, Point &);
	int x, y;
};

}

#endif	//__POINT_H__
