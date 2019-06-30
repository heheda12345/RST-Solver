#include "PrimSMST.h"
namespace RECTILINEAR_STEINER_TREE {
void PrimSMST::run(PointSet& ps, MST& mst)
{
	using namespace std;
	int n=ps.size();
	vector<bool> vis(n);
	vector<int> dis(n);
	vis[0]=1;
	for(int i=1;i<n;i++)
	{
		vis[i]=0;
		dis[i]=0;
	}
	getMSTTree(mst).clear();
	for(int i=0;i<n-1;i++)
	{
		int y=-1;
		for(int j=0;j<n;j++)
		{
			if(vis[j]==1)
				continue;
			if(y==-1||getTuple3(ps[y],ps[dis[y]])>getTuple3(ps[j],ps[dis[j]]))
				y=j;
		}
		vis[y]=1;
		getMSTTree(mst).push_back(pair<Point,Point>(ps[y],ps[dis[y]]));
		for(int j=0;j<n;j++)
		{
			if(vis[j]==1)
				continue;
			if(getTuple3(ps[j],ps[dis[j]])>getTuple3(ps[j],ps[y]))
				dis[j]=y;
		}
	}
}
}
