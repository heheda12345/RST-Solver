#ifndef UNION_H
#define UNION_H

namespace RECTILINEAR_STEINER_TREE {
class Union
{
public:
    Union(int n);
    virtual ~Union();
    Union(const Union& other) = delete;
    Union& operator=(const Union& other) = delete;
    int find(int x);
    bool add(int x, int y);

private:
    int *fa;
};
}

#endif // UNION_H
