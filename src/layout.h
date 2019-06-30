#ifndef __LAYOUT_H__
#define __LAYOUT_H__
#include <ostream>
#include <istream>
#include <vector>

#include "pointset.h"

namespace RECTILINEAR_STEINER_TREE {
class Layout
{
	friend class RST;

public:
	friend std::ostream & operator << (std::ostream &out, const Layout &);
	friend std::istream & operator >> (std::istream &in, Layout &);
	bool checkValidity()const;
	int value()const;
	struct Wire
	{
		Point a, b;
		Wire(): a(0, 0), b(0, 0) {}
		Wire(const Point &_, const Point &__): a(_), b(__) {}
		int length()const {return a.dist(b);}
	};
	const PointSet &getPointSet()const {return pointSet;}
	const std::vector<Wire> &getWires()const {return wires;}

private:
	PointSet pointSet;
	std::vector<Wire> wires;
	int m_value;
};

}

#endif	//__LAYOUT_H__
