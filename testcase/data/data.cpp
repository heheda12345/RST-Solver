#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,bool>mp;
int main()
{
	freopen("../input8.in","w",stdout);
	srand(time(NULL));
	int n=50000;
	printf("%d\n",n);
	for(int i=0;i<n;i++)
	{
		int x,y;
		do
		{
			x=rand()%1000,y=rand()%1000;
		}while(mp[pair<int,int>(x,y)]==1);
		mp[pair<int,int>(x,y)]=1;
		printf("%d %d\n",x,y);
	}
	return 0;
}
