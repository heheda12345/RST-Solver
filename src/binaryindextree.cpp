#include "binaryindextree.h"
#include <climits>
#include <cstring>
#include <vector>
#include <cstdio>
namespace RECTILINEAR_STEINER_TREE {

using namespace std;

BinaryIndexTree::BinaryIndexTree(int n_) : n(n_)
{
    c = new int[n + 5];
    d = new int[n + 5];
    for (int i = 0; i < n; i++) c[i] = INT_MIN;
    memset(d, 0, sizeof(d));
}

BinaryIndexTree::~BinaryIndexTree()
{
    delete []c;
    delete []d;
}

vector<int> BinaryIndexTree::get(int x)
{
    vector<int> ans;
    int mx = INT_MIN;
    for (; x; x -= x & (-x))
    {
        if (c[x] > mx)
        {
            mx = c[x];
            ans.clear();
        }
        if (c[x] == mx && mx != INT_MIN)
        {
            ans.push_back(d[x]);
        }
    }
    return ans;
}

void BinaryIndexTree::add(int x, int de, int id)
{
    for (int i = x; i <= n; i += i & (-i))
        if (c[i] < de) c[i] = de, d[i] = id;
}
}

