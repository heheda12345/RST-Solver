#ifndef __MST_H__
#define __MST_H__

#include <vector>

#include "pointset.h"

namespace RECTILINEAR_STEINER_TREE {
class MST
{
	friend class SMST;
public:
	const std::vector<std::pair<Point, Point> > &getTree()const {return tree;}

private:
	std::vector<std::pair<Point, Point> > tree;
};

}

#endif	//__MST_H__
