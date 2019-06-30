#include <map>
#include <vector>

#include "layout.h"

namespace RECTILINEAR_STEINER_TREE {
using namespace std;
void checkValidityDfs(Point x, const vector<Layout::Wire> &wires, map<Point, bool> &vis)
{
	if (vis[x])	return ;
	vis[x] = 1;
	for (int i = 0; i < (int)wires.size(); i++)
	{
		if (wires[i].a.x == wires[i].b.x && wires[i].a.x == x.x)
		{
			if (min(wires[i].a.y, wires[i].b.y) <= x.y && x.y <= max(wires[i].a.y, wires[i].b.y))
				checkValidityDfs(wires[i].b, wires, vis), checkValidityDfs(wires[i].a, wires, vis);
		}
		if (wires[i].a.y == wires[i].b.y && wires[i].a.y == x.y)
		{
			if (min(wires[i].a.x, wires[i].b.x) <= x.x && x.x <= max(wires[i].a.x, wires[i].b.x))
				checkValidityDfs(wires[i].b, wires, vis), checkValidityDfs(wires[i].a, wires, vis);
		}
	}
}

bool Layout::checkValidity()const
{
	using namespace std;
	map<Point, bool> vis;
	checkValidityDfs(pointSet[0], wires, vis);
	for (int i = 0; i < (int)pointSet.size(); i++)
	{
		if (vis[pointSet[i]] == 0)
			return 0;
	}
	return 1;
}

int Layout::value()const
{
	return m_value;
}

std::ostream & operator << (std::ostream &out, const Layout &l)
{
	using namespace std;
	out << l.value() << endl;
	out << (int)l.pointSet.size() << endl;
	for (int i = 0; i < (int)l.pointSet.size(); i++)
	{
		out << l.pointSet[i] << " ";
	}
	out << endl << (int)l.wires.size() << endl;
	for (int i = 0; i < (int)l.wires.size(); i++)
	{
		out << l.wires[i].a << " " << l.wires[i].b << endl;
	}
	return out;
}
std::istream & operator >> (std::istream &in, Layout &l)
{
	using namespace std;
	l.pointSet.clear();
	l.wires.clear();
	int n;
	in >> l.m_value;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		Point p;
		in >> p;
		l.pointSet.push_back(p);
	}
	in >> n;
	for (int i = 0; i < n; i++)
	{
		Layout::Wire w;
		in >> w.a >> w.b;
		l.wires.push_back(w);
	}
	return in;
}

}
