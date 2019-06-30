#ifndef TREE_H
#define TREE_H
#include <string.h>
#include <iostream>
namespace RECTILINEAR_STEINER_TREE
{
class Tree
{
public:
	int *to, *next, *st;
	int tot;
	Tree()
	{
		tot = -1;
	}
	void init(int n)
	{
		tot = -1;
		to = new int[n * 2 + 3];
		next = new int[n * 2 + 3];
		st = new int[n + 3];
		memset(st, -1, sizeof(int) * (n + 3));
	}
	void add(int u, int v)
	{
		tot++;
		to[tot] = v;
		next[tot] = st[u];
		st[u] = tot;
	}
};



}
#endif //TREE_H
