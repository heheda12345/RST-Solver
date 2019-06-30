#ifndef RST_H
#define RST_H
#include <map>
#include <vector>

#include "mst.h"
#include "tree.h"
#include "layout.h"

namespace RECTILINEAR_STEINER_TREE {
class MST;
class Layout;

class RST
{
public:
	RST() = default;
	virtual ~RST() = default;
	virtual void run(MST&, Layout&) = 0;
	void init(MST& mst, Layout& layout);
	int getRoot(Tree & tree, int now, int fa);

protected:
	std::map <Point, int> mp;
	std::vector<Point> mstPoints;
	Tree tree;
	int root;
	PointSet &getPointSet(Layout &l) {return l.pointSet;}
	std::vector<Layout::Wire> &getWires(Layout &l) {return l.wires;}
	int &getValue(Layout &l) {return l.m_value;}
};
}

#endif // RST_H
