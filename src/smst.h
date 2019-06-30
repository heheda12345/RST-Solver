#ifndef SMST_H
#define SMST_H
#include <algorithm>

#include "mst.h"
#include "pointset.h"
namespace RECTILINEAR_STEINER_TREE {

typedef std::pair<int, std::pair<int, int> > Tuple3;

class MST;

class SMST
{
public:
	SMST() = default;
	virtual ~SMST() = default;
	virtual void run(PointSet&, MST&) = 0;
	static Tuple3 getTuple3(const Point &a, const Point &b) {return Tuple3(dist(a, b), std::pair<int, int>(-abs(a.y - b.y), -std::max(a.x, b.x)));}

protected:
	std::vector<std::pair<Point, Point> > &getMSTTree(MST &mst);
};

}

#endif // SMST_H
