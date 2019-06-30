#ifndef LRST_H
#define LRST_H
#include <map>
#include "rst.h"

namespace RECTILINEAR_STEINER_TREE {
class LRST : public RST
{
public:
    LRST() = default;
    virtual ~LRST() = default;
    void run(MST&, Layout&) override;
    void dfs(int now, int fa, Layout &layout);
    void addLine(std::map<int, std::pair<int, int>> &Line, int pos, int l, int r);
    int dis(Point a, Point b);
    void calcWire(int now, int fa, Layout &layout, bool U);

private:
    int *maxOverlapU, *maxOverlapL, *choiceU, *choiceL;
};
}

#endif // LRST_H
