#include <map>
#include <vector>

#include "lrst.h"

using namespace std;

namespace RECTILINEAR_STEINER_TREE
{
int LRST::dis(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void LRST::addLine(map<int, pair<int, int>> &Line, int pos, int l, int r)
{
	if (l > r)
		swap(l, r);
	if (Line.find(pos) == Line.end())
		Line[pos] = pair<int, int>(l, r);
	else
	{
		int tmpl = Line[pos].first, tmpr = Line[pos].second;
		Line[pos] = pair<int, int>(min(tmpl, l), max(tmpr, r));
	}
}

void LRST::calcWire(int now, int fa, Layout &layout, bool U) //true U false L
{
	int sonNum = 0;
	int sons[10];
	for (int i = tree.st[now]; i != -1; i = tree.next[i])
		if (tree.to[i] != fa)
			sons[sonNum++] = tree.to[i];
	int choice;
	if (U)
		choice = choiceU[now];
	else
		choice = choiceL[now];

	map<int, pair<int, int>> xLine, yLine;
	for (int j = 0; j < sonNum; j++)
	{

		if (((mstPoints[sons[j]].y > mstPoints[now].y) ^ (((1 << j)&choice)) != 0))
		{
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[sons[j]].x, mstPoints[sons[j]].y), Point(mstPoints[sons[j]].x, mstPoints[now].y)));
			if (getWires(layout).back().a == getWires(layout).back().b)
				getWires(layout).pop_back();
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[sons[j]].x, mstPoints[now].y), Point(mstPoints[now].x, mstPoints[now].y)));
			if (getWires(layout).back().a == getWires(layout).back().b)
				getWires(layout).pop_back();
		}
		else
		{
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[sons[j]].x, mstPoints[sons[j]].y), Point(mstPoints[now].x, mstPoints[sons[j]].y)));
			if (getWires(layout).back().a == getWires(layout).back().b)
				getWires(layout).pop_back();
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[now].x, mstPoints[sons[j]].y), Point(mstPoints[now].x, mstPoints[now].y)));
			if (getWires(layout).back().a == getWires(layout).back().b)
				getWires(layout).pop_back();
		}
	}


	for (int i = 0; i < sonNum; i++)
		calcWire(sons[i], now, layout, (1 << i)&choice);
}

void LRST::dfs(int now, int fa, Layout &layout)
{
	maxOverlapU[now] = maxOverlapL[now] = 0;
	choiceU[now] = choiceL[now] = 0;
	int sonNum = 0;
	int sons[10];
	for (int i = tree.st[now]; i != -1; i = tree.next[i])
		if (tree.to[i] != fa)
		{
			//cout<<now<<"->"<<tree.to[i]<<endl;
			sons[sonNum++] = tree.to[i];
			getValue(layout) += dis(mstPoints[now], mstPoints[tree.to[i]]);
			dfs(tree.to[i], now, layout);
		}


	//NOW L
	//cout<<"in"<<now<<" "<<sonNum<<endl;
	map<int, pair<int, int>> xLine, yLine;
	for (int i = 0; i < (1 << sonNum); i++)
	{
		//0->L
		//1->U
		xLine.clear();
		yLine.clear();
		for (int j = 0; j < sonNum; j++)
		{
			if ((mstPoints[sons[j]].y > mstPoints[now].y) ^ (((1 << j)&i) != 0))
			{
				addLine(yLine, mstPoints[sons[j]].x, mstPoints[sons[j]].y, mstPoints[now].y);

				addLine(xLine, mstPoints[now].y, mstPoints[sons[j]].x, mstPoints[now].x);
			}
			else
			{
				addLine(xLine, mstPoints[sons[j]].y, mstPoints[sons[j]].x, mstPoints[now].x);

				addLine(yLine, mstPoints[now].x, mstPoints[sons[j]].y, mstPoints[now].y);

			}
		}

		//加向父节点的边
		if (fa != -1)
		{
			if (mstPoints[fa].y > mstPoints[now].y)
			{
				addLine(yLine, mstPoints[fa].x, mstPoints[fa].y, mstPoints[now].y);

				addLine(xLine, mstPoints[now].y, mstPoints[fa].x, mstPoints[now].x);
			}
			else
			{
				addLine(xLine, mstPoints[fa].y, mstPoints[fa].x, mstPoints[now].x);

				addLine(yLine, mstPoints[now].x, mstPoints[fa].y, mstPoints[now].y);

			}
		}
		int tmp = 0;
		for (int j = 0; j < sonNum; j++)
		{
			tmp += dis(mstPoints[sons[j]], mstPoints[now]);
			if ((1 << j)&i)
				tmp += maxOverlapU[sons[j]];
			else
				tmp += maxOverlapL[sons[j]];
		}
		if (fa != -1)
			tmp += dis(mstPoints[now], mstPoints[fa]);
		//if(now==13)
		//	cout<<tmp<<" "<<i<<endl;
		map<int, pair<int, int>>::iterator it;
		for (it = xLine.begin(); it != xLine.end(); it++)
			tmp -= (it->second).second - (it->second).first;

		for (it = yLine.begin(); it != yLine.end(); it++)
			tmp -= (it->second).second - (it->second).first;
		//if(now==2)
		//	cout<<tmp<<" "<<i<<endl;
		if (tmp >= maxOverlapL[now])
		{
			//cout<<tmp<<" "<<i<<endl;
			maxOverlapL[now] = tmp;
			choiceL[now] = i;
		}
	}
	//now U
	for (int i = 0; i < (1 << sonNum); i++)
	{
		//0->L
		//1->U
		xLine.clear();
		yLine.clear();
		for (int j = 0; j < sonNum; j++)
		{
			if ((mstPoints[sons[j]].y > mstPoints[now].y) ^ (((1 << j)&i) != 0))
			{
				//if(now==2&&i==4)
				//	cout<<sons[j]<<"!"<<endl;
				addLine(yLine, mstPoints[sons[j]].x, mstPoints[sons[j]].y, mstPoints[now].y);

				addLine(xLine, mstPoints[now].y, mstPoints[sons[j]].x, mstPoints[now].x);
			}
			else
			{
				addLine(xLine, mstPoints[sons[j]].y, mstPoints[sons[j]].x, mstPoints[now].x);

				addLine(yLine, mstPoints[now].x, mstPoints[sons[j]].y, mstPoints[now].y);

			}
		}

		//加向父节点的边
		if (fa != -1)
		{
			if (mstPoints[fa].y <= mstPoints[now].y)
			{
				addLine(yLine, mstPoints[fa].x, mstPoints[fa].y, mstPoints[now].y);

				addLine(xLine, mstPoints[now].y, mstPoints[fa].x, mstPoints[now].x);
			}
			else
			{
				addLine(xLine, mstPoints[fa].y, mstPoints[fa].x, mstPoints[now].x);

				addLine(yLine, mstPoints[now].x, mstPoints[fa].y, mstPoints[now].y);

			}
		}
		int tmp = 0;
		for (int j = 0; j < sonNum; j++)
		{
			tmp += dis(mstPoints[sons[j]], mstPoints[now]);
			if ((1 << j)&i)
				tmp += maxOverlapU[sons[j]];
			else
				tmp += maxOverlapL[sons[j]];
		}
		if (fa != -1)
			tmp += dis(mstPoints[now], mstPoints[fa]);
		//if(now==13)
		//	cout<<tmp<<" "<<i<<endl;
		map<int, pair<int, int>>::iterator it;
		for (it = xLine.begin(); it != xLine.end(); it++)
			tmp -= (it->second).second - (it->second).first;

		for (it = yLine.begin(); it != yLine.end(); it++)
			tmp -= (it->second).second - (it->second).first;

		/*if(now==2)
		{
			cout<<tmp<<" "<<i<<endl;
			for(it=xLine.begin();it!=xLine.end();it++)
				cout<<it->first<<" "<<(it->second).second<<" "<<(it->second).first<<endl;
			cout<<"------"<<endl;
			for(it=yLine.begin();it!=yLine.end();it++)
				cout<<it->first<<" "<<(it->second).second<<" "<<(it->second).first<<endl;
		}*/
		if (tmp >= maxOverlapU[now])
		{
			//cout<<tmp<<" "<<i<<endl;
			maxOverlapU[now] = tmp;
			choiceU[now] = i;
		}
	}
	//cout<<choiceL[now]<<" "<<choiceU[now]<<endl;
	//cout<<"out"<<now<<endl;
}



void LRST::run(MST &mst, Layout & layout)
{
	init(mst, layout);
	int PointNum = mst.getTree().size() + 1;
	maxOverlapU = new int[PointNum + 2];
	maxOverlapL = new int[PointNum + 2];
	choiceU = new int[PointNum + 2];
	choiceL = new int[PointNum + 2];
	for (int i = 0; i < PointNum; i++)
		getPointSet(layout).push_back(mstPoints[i]);
	getValue(layout) = 0;
	dfs(root, -1, layout);
	if (maxOverlapU[root] < maxOverlapL[root])
		calcWire(root, -1, layout, 0);
	else
		calcWire(root, -1, layout, 1);
	getValue(layout) -= max(maxOverlapU[root], maxOverlapL[root]);
	delete maxOverlapU;
	delete maxOverlapL;
	delete choiceU;
	delete choiceL;
}
}
