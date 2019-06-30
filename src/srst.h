#ifndef SRST_H
#define SRST_H
#include <map>
#include <vector>
#include "rst.h"

namespace RECTILINEAR_STEINER_TREE {
class SRST : public RST
{
public:
    SRST() = default;
    virtual ~SRST() = default;
    void run(MST&, Layout&) override;
    void dfs(int now, int fa, Layout &layout);
    void addLine(std::map<int, std::pair<int, int>> &Line, int pos, int l, int r);
    int dis(Point a, Point b);
    void calcWire(int now, int fa, Layout &layout, int curchoice);
    void Calc(int now, int fa, Layout &layout, std::vector<int> &choice, int cur, int sonNum, int *sons);

private:
    std::vector <int> *maxOverlapX, *maxOverlapY;
    std::vector <std::vector<int>> *choiceX, *choiceY;
    std::vector <int> xValidPositions, yValidPositions;
    std::vector <int> xPosition, yPosition, limitX, limitY; //limit[i]->i向父亲有几个可行的xPos
};

}

#endif // SRST_H
