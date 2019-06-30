#include <map>
#include <vector>

#include "srst.h"
#include <bits/stdc++.h>

using namespace std;

namespace RECTILINEAR_STEINER_TREE
{
int SRST::dis(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void SRST::addLine(map<int, pair<int, int>> &Line, int pos, int l, int r)
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

void SRST::calcWire(int now, int fa, Layout &layout, int curchoice)
{
	//cout<<now<<endl;
	int sonNum = 0;
	int sons[10];
	for (int i = tree.st[now]; i != -1; i = tree.next[i])
		if (tree.to[i] != fa)
			sons[sonNum++] = tree.to[i];
	for (int i = 0; i < sonNum; i++)
	{
		int tmp;
		if (curchoice < 0)
			tmp = choiceY[now][-(curchoice + 1)][i];
		else
			tmp = choiceX[now][curchoice][i];
		//cout<<sons[i]<<" "<<tmp<<endl;
		calcWire(sons[i], now, layout, tmp);
	}
	if (fa == -1)
		return;
	if (curchoice >= 0)
	{
		if (mstPoints[now].x < mstPoints[fa].x)
		{
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, mstPoints[fa].y), Point(xValidPositions[xPosition[now] + curchoice], mstPoints[fa].y)));
			getWires(layout).push_back(Layout::Wire(Point(xValidPositions[xPosition[now] + curchoice], mstPoints[fa].y), Point(xValidPositions[xPosition[now] + curchoice], mstPoints[now].y)));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[now].x, mstPoints[now].y), Point(xValidPositions[xPosition[now] + curchoice], mstPoints[now].y)));

		}
		else
		{

			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, mstPoints[fa].y), Point(xValidPositions[xPosition[now] - curchoice], mstPoints[fa].y)));
			getWires(layout).push_back(Layout::Wire(Point(xValidPositions[xPosition[now] - curchoice], mstPoints[fa].y), Point(xValidPositions[xPosition[now] - curchoice], mstPoints[now].y)));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[now].x, mstPoints[now].y), Point(xValidPositions[xPosition[now] - curchoice], mstPoints[now].y)));

		}
	}
	else
	{
		curchoice = -(curchoice + 1);
		if (mstPoints[now].y < mstPoints[fa].y)
		{
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, mstPoints[fa].y), Point(mstPoints[fa].x, yValidPositions[yPosition[now] + curchoice])));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, yValidPositions[yPosition[now] + curchoice]), Point(mstPoints[now].x, yValidPositions[yPosition[now] + curchoice])));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[now].x, mstPoints[now].y), Point(mstPoints[now].x, yValidPositions[yPosition[now] + curchoice])));
		}
		else
		{
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, mstPoints[fa].y), Point(mstPoints[fa].x, yValidPositions[yPosition[now] - curchoice])));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[fa].x, yValidPositions[yPosition[now] - curchoice]), Point(mstPoints[now].x, yValidPositions[yPosition[now] - curchoice])));
			getWires(layout).push_back(Layout::Wire(Point(mstPoints[now].x, mstPoints[now].y), Point(mstPoints[now].x, yValidPositions[yPosition[now] - curchoice])));

		}
	}

}

void SRST::Calc(int now, int fa, Layout &layout, vector<int> &choice, int cur, int sonNum, int *sons)
{
	//cout<<cur<<endl;

	/*cout<<cur<<" "<<choice.size()<<endl;
	for(int i=0;i<choice.size();i++)
		cout<<choice[i]<<" ";
	cout<<endl;*/
	if (cur == sonNum) //儿子都确定了
	{
		//cout<<"in"<<endl;
		for (int i = 0; i < limitX[now]; i++)
		{
			map<int, pair<int, int>> xLine, yLine;
			if (fa != -1)
			{
				if (mstPoints[fa].x > mstPoints[now].x)
				{
					addLine(xLine, mstPoints[fa].y, mstPoints[fa].x, xValidPositions[xPosition[now] + i]);
					addLine(yLine, xValidPositions[xPosition[now] + i], mstPoints[fa].y, mstPoints[now].y);
					addLine(xLine, mstPoints[now].y, xValidPositions[xPosition[now] + i], mstPoints[now].x);
				}
				else
				{
					addLine(xLine, mstPoints[fa].y, mstPoints[fa].x, xValidPositions[xPosition[now] - i]);
					addLine(yLine, xValidPositions[xPosition[now] - i], mstPoints[fa].y, mstPoints[now].y);
					addLine(xLine, mstPoints[now].y, xValidPositions[xPosition[now] - i], mstPoints[now].x);
				}
			}
			for (int j = 0; j < sonNum; j++)
			{
				int tmp = choice[j];
				if (tmp >= 0)
				{
					if (mstPoints[sons[j]].x > mstPoints[now].x)
						tmp *= -1;
					addLine(xLine, mstPoints[sons[j]].y, mstPoints[sons[j]].x, xValidPositions[xPosition[sons[j]] + tmp]);
					addLine(yLine, xValidPositions[xPosition[sons[j]] + tmp], mstPoints[sons[j]].y, mstPoints[now].y);
					addLine(xLine, mstPoints[now].y, xValidPositions[xPosition[sons[j]] + tmp], mstPoints[now].x);
				}
				else
				{
					tmp = -(tmp + 1);
					if (mstPoints[sons[j]].y > mstPoints[now].y)
						tmp *= -1;
					addLine(yLine, mstPoints[sons[j]].x, mstPoints[sons[j]].y, yValidPositions[yPosition[sons[j]] + tmp]);
					addLine(xLine, yValidPositions[yPosition[sons[j]] + tmp], mstPoints[sons[j]].x, mstPoints[now].x);
					addLine(yLine, mstPoints[now].x, yValidPositions[yPosition[sons[j]] + tmp], mstPoints[now].y);
				}
			}
			int ret = 0;
			//cout<<"###"<<endl;
			for (int j = 0; j < sonNum; j++)
			{
				//cout<<j<<endl;
				ret += dis(mstPoints[sons[j]], mstPoints[now]);
				int tmp = choice[j];
				//cout<<sons[j]<<" "<<tmp<<endl;
				if (tmp >= 0)
					ret += maxOverlapX[sons[j]][tmp];
				else
				{
					tmp = -(tmp + 1);
					ret += maxOverlapY[sons[j]][tmp];
				}
			}
			//cout<<"@#$"<<endl;
			if (fa != -1)
				ret += dis(mstPoints[now], mstPoints[fa]);
			map<int, pair<int, int>>::iterator it;
			for (it = xLine.begin(); it != xLine.end(); it++)
				ret -= (it->second).second - (it->second).first;

			for (it = yLine.begin(); it != yLine.end(); it++)
				ret -= (it->second).second - (it->second).first;
			if (ret >= maxOverlapX[now][i])
			{
				maxOverlapX[now][i] = ret;
				choiceX[now][i].assign(choice.begin(), choice.end());
			}
			//[now][i]
		}
		//cout<<"mid"<<endl;
		for (int i = 0; i < limitY[now]; i++)
		{
			map<int, pair<int, int>> xLine, yLine;
			if (fa != -1)
			{
				if (mstPoints[fa].y > mstPoints[now].y)
				{
					addLine(yLine, mstPoints[fa].x, mstPoints[fa].y, yValidPositions[yPosition[now] + i]);
					addLine(xLine, yValidPositions[yPosition[now] + i], mstPoints[fa].x, mstPoints[now].x);
					addLine(yLine, mstPoints[now].x, yValidPositions[yPosition[now] + i], mstPoints[now].y);
				}
				else
				{
					addLine(yLine, mstPoints[fa].x, mstPoints[fa].y, yValidPositions[yPosition[now] - i]);
					addLine(xLine, yValidPositions[yPosition[now] - i], mstPoints[fa].x, mstPoints[now].x);
					addLine(yLine, mstPoints[now].x, yValidPositions[yPosition[now] - i], mstPoints[now].y);
				}
			}
			for (int j = 0; j < sonNum; j++)
			{
				int tmp = choice[j];
				if (tmp >= 0)
				{
					if (mstPoints[sons[j]].x > mstPoints[now].x)
						tmp *= -1;
					addLine(xLine, mstPoints[sons[j]].y, mstPoints[sons[j]].x, xValidPositions[xPosition[sons[j]] + tmp]);
					addLine(yLine, xValidPositions[xPosition[sons[j]] + tmp], mstPoints[sons[j]].y, mstPoints[now].y);
					addLine(xLine, mstPoints[now].y, xValidPositions[xPosition[sons[j]] + tmp], mstPoints[now].x);
				}
				else
				{
					tmp = -(tmp + 1);
					if (mstPoints[sons[j]].y > mstPoints[now].y)
						tmp *= -1;
					addLine(yLine, mstPoints[sons[j]].x, mstPoints[sons[j]].y, yValidPositions[yPosition[sons[j]] + tmp]);
					addLine(xLine, yValidPositions[yPosition[sons[j]] + tmp], mstPoints[sons[j]].x, mstPoints[now].x);
					addLine(yLine, mstPoints[now].x, yValidPositions[yPosition[sons[j]] + tmp], mstPoints[now].y);
				}
			}
			int ret = 0;
			for (int j = 0; j < sonNum; j++)
			{
				ret += dis(mstPoints[sons[j]], mstPoints[now]);
				int tmp = choice[j];
				if (tmp >= 0)
					ret += maxOverlapX[sons[j]][tmp];
				else
				{
					tmp = -(tmp + 1);
					ret += maxOverlapY[sons[j]][tmp];
				}
			}
			if (fa != -1)
				ret += dis(mstPoints[now], mstPoints[fa]);
			map<int, pair<int, int>>::iterator it;
			for (it = xLine.begin(); it != xLine.end(); it++)
				ret -= (it->second).second - (it->second).first;

			for (it = yLine.begin(); it != yLine.end(); it++)
				ret -= (it->second).second - (it->second).first;

			if (ret >= maxOverlapY[now][i])
			{
				maxOverlapY[now][i] = ret;
				choiceY[now][i].assign(choice.begin(), choice.end());
			}
			//[now][i]
		}
		//cout<<"out"<<endl;
		return;
	}
	for (int i = 0; i < limitX[sons[cur]]; i++)
	{
		//cout<<i<<"!"<<endl;
		//cout<<"size"<<choice.size()<<endl;
		choice[cur] = i;
		Calc(now, fa, layout, choice, cur + 1, sonNum, sons);
	}
	for (int i = 0; i < limitY[sons[cur]]; i++)
	{
		//cout<<i<<"@"<<endl;
		choice[cur] = -i - 1;
		Calc(now, fa, layout, choice, cur + 1, sonNum, sons);
	}
}

void SRST::dfs(int now, int fa, Layout &layout)
{
	//cout<<now<<endl;
	for (int i = 0; i < limitX[now]; i++)
		maxOverlapX[now].push_back(0);
	for (int i = 0; i < limitY[now]; i++)
		maxOverlapY[now].push_back(0);
	choiceX[now].resize(limitX[now]);
	choiceY[now].resize(limitY[now]);
	int sonNum = 0;
	int sons[10];
	for (int i = tree.st[now]; i != -1; i = tree.next[i])
		if (tree.to[i] != fa)
		{
			//cout<<now<<"->"<<tree.to[i]<<endl;
			sons[sonNum++] = tree.to[i];
			limitX[tree.to[i]] = abs(xPosition[now] - xPosition[tree.to[i]]) + 1;
			limitY[tree.to[i]] = abs(yPosition[now] - yPosition[tree.to[i]]) + 1;
			getValue(layout) += dis(mstPoints[now], mstPoints[tree.to[i]]);
			dfs(tree.to[i], now, layout);
		}
	map<int, pair<int, int>> xLine, yLine;
	vector<int> choice;//+X -Y
	choice.resize(sonNum + 1);
	//cout<<"inCalc"<<now<<" "<<sonNum<<" "<<choice.size()<<endl;
	Calc(now, fa, layout, choice, 0, sonNum, sons);
	//cout<<"outCalc"<<now<<endl;
}

void SRST::run(MST &mst, Layout & layout)
{
	init(mst, layout);
	int PointNum = mst.getTree().size() + 1;
	maxOverlapX = new vector<int>[PointNum + 2]; //maxOverlapU[now][i]为now节点向U第i个拐
	maxOverlapY = new vector<int>[PointNum + 2];
	choiceX = new vector<vector<int>>[PointNum + 2]; //choiceU[now][i]为now节点U第i个拐的时候怎么选
	choiceY = new vector<vector<int>>[PointNum + 2];
	limitX.resize(PointNum + 2);
	limitY.resize(PointNum + 2);
	for (int i = 0; i < PointNum; i++)
		getPointSet(layout).push_back(mstPoints[i]);
	getValue(layout) = 0;

	for (int i = 0; i < PointNum; i++)
	{
		xValidPositions.push_back(mstPoints[i].x);
		yValidPositions.push_back(mstPoints[i].y);
	}
	sort(xValidPositions.begin(), xValidPositions.end());
	sort(yValidPositions.begin(), yValidPositions.end());
	unique(xValidPositions.begin(), xValidPositions.end());
	unique(yValidPositions.begin(), yValidPositions.end());
	for (int i = 0; i < PointNum; i++)
	{
		xPosition.push_back(lower_bound(xValidPositions.begin(), xValidPositions.end(), mstPoints[i].x) - xValidPositions.begin());
		yPosition.push_back(lower_bound(yValidPositions.begin(), yValidPositions.end(), mstPoints[i].y) - yValidPositions.begin());
	}
	limitX[root] = limitY[root] = 1;
	//cout<<"!!!"<<endl;
	dfs(root, -1, layout);
	//cout<<"!!!"<<endl;
	if (maxOverlapX[root][0] > maxOverlapY[root][0])
		calcWire(root, -1, layout, 0);
	else
		calcWire(root, -1, layout, -1);
	getValue(layout) -= max(maxOverlapX[root][0], maxOverlapY[root][0]);
	//cout<<"!!!"<<endl;
}
}
