#include "optsmst.h"
#include <algorithm>

#include "union.h"
#include "binaryindextree.h"
#include "timerecorder.h"

namespace RECTILINEAR_STEINER_TREE {

using namespace std;

struct IDPoint
{
	Point p;
	int id;
	IDPoint(Point p_, int id_) : p(p_), id(id_) {}
};

typedef pair<int, int> Line;

void discretize(int n, int *a)
{
	int *b = new int[n + 5];
	for (int i = 0; i < n; i++)
		b[i] = a[i];
	sort(b, b + n);
	int m = unique(b, b + n) - b;
	for (int i = 0; i < n; i++)
		a[i] = lower_bound(b, b + m, a[i]) - b + 1;
	delete b;
}

void oneDirection(vector<IDPoint>& p, vector<Line> &lines)
{
	int n = p.size();
	auto cmp = [] (const IDPoint & a, const IDPoint & b)
	{
		return a.p.x == b.p.x ? a.p.x + a.p.y < b.p.x + b.p.y : a.p.x > b.p.x;
	};
	sort(p.begin(), p.end(), cmp);

	int *a = new int[n + 5];
	for (int i = 0; i < n; i++)
		a[i] = p[i].p.x + p[i].p.y;
	discretize(n, a);

	BinaryIndexTree bit(n);
	for (int i = 0; i < n; i++)
	{
		vector<int> neighbor = bit.get(a[i]);
		for (int j : neighbor)
			lines.push_back(Line(p[i].id, p[j].id));
		bit.add(a[i], p[i].p.y - p[i].p.x, i);
	}
}

void getLines(vector<IDPoint>& p, vector<Line> &lines)
{
	int n = p.size();
	lines.clear();
	oneDirection(p, lines);

	for (int i = 0; i < n; i++)
		swap(p[i].p.x, p[i].p.y);
	oneDirection(p, lines);

	for (int i = 0; i < n; i++)
		p[i].p.x = -p[i].p.x;
	oneDirection(p, lines);

	for (int i = 0; i < n; i++)
		swap(p[i].p.x, p[i].p.y);
	oneDirection(p, lines);
}
void kruscal(vector<IDPoint>& p, vector<Line> lines, vector<pair<Point, Point> > &mst)
{
	mst.clear();
	auto cmpID = [] (const IDPoint & a, const IDPoint & b)
	{
		return a.id < b.id;
	};
	sort(p.begin(), p.end(), cmpID);
	auto cmpLine = [&p] (const Line & a, const Line & b)
	{
		return OptSMST::getTuple3(p[a.first].p, p[a.second].p) < OptSMST::getTuple3(p[b.first].p, p[b.second].p);
	};
	sort(lines.begin(), lines.end(), cmpLine);

	Union u(p.size());
	for (const Line& line : lines)
	{
		int x = line.first, y = line.second;
		if (u.add(x, y))
			mst.push_back(make_pair(p[x].p, p[y].p));
	}
}

void OptSMST::run(PointSet& ps, MST& mst)
{
	vector<IDPoint> p;
	vector<Line> lines;
	int n = ps.size();
	for (int i = 0; i < n; i++)
		p.push_back(IDPoint(ps[i], i));
	getLines(p, lines);
	kruscal(p, lines, getMSTTree(mst));
}

}

