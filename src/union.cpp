#include "union.h"
namespace RECTILINEAR_STEINER_TREE {
Union::Union(int n)
{
    fa = new int[n];
    for (int i = 0; i < n; i++)
        fa[i] = i;
}

Union::~Union()
{
    delete []fa;
}

int Union::find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool Union::add(int x, int y)
{
    int f1 = find(x), f2 = find(y);
    if (f1 != f2)
    {
        fa[f1] = f2;
        return 1;
    }
    return 0;
}

}
