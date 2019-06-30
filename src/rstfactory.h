#ifndef RSTFACTORY_H
#define RSTFACTORY_H

#include "rst.h"

namespace RECTILINEAR_STEINER_TREE {
class RSTFactory
{
public:
	RSTFactory() = default;
	virtual ~RSTFactory() = default;
	virtual RST* generateRST() = 0;
};
}

#endif // RSTFACTORY_H
