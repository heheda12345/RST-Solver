#ifndef BINARYINDEXTREE_H
#define BINARYINDEXTREE_H

#include <vector>

namespace RECTILINEAR_STEINER_TREE {
class BinaryIndexTree
{
public:
    BinaryIndexTree(int n_);
    BinaryIndexTree(const BinaryIndexTree&) = delete;
    virtual ~BinaryIndexTree();
    std::vector<int> get(int x);
    void add(int x, int data, int id);
    BinaryIndexTree& operator = (const BinaryIndexTree& other) = delete;

private:
    int *c, *d;
    int n;
};
}
#endif // BINARYINDEXTREE_H
