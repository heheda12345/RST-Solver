#include "rst.h"
#include <bits/stdc++.h>
using namespace std;

namespace RECTILINEAR_STEINER_TREE {

int RST::getRoot(Tree & tree, int now, int fa)
{
	bool leaf = true;
	for (int i = tree.st[now]; i != -1; i = tree.next[i])
		if (tree.to[i] != fa)
		{
			leaf = false;
			int tmp = RST::getRoot(tree, tree.to[i], now);
			if (tmp)
				return tmp;
		}
	if (leaf)
		return now;
	return 0;
}
void RST::init(MST& mst, Layout& layout)
{
	const vector<pair<Point, Point>> &mstEdges = mst.getTree();
	int PointsNum = 0; //number of Points
	for (int i = 0; i < mstEdges.size(); i++)
	{
		if (mp.find(mstEdges[i].first) == mp.end())
		{
			mstPoints.push_back(mstEdges[i].first);
			mp[mstEdges[i].first] = PointsNum++;
		}
		if (mp.find(mstEdges[i].second) == mp.end())
		{
			mstPoints.push_back(mstEdges[i].second);
			mp[mstEdges[i].second] = PointsNum++;
		}
	}
	tree.init(PointsNum);
	for (int i = 0; i < mstEdges.size(); i++)
	{
		tree.add(mp[mstEdges[i].first], mp[mstEdges[i].second]);
		tree.add(mp[mstEdges[i].second], mp[mstEdges[i].first]);
	}
	//cout<<"Before get root"<<endl;
	root = getRoot(tree, 0, -1);
	//cout<<"after getroot"<<endl;
}


}
