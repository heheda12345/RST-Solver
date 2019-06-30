#ifndef SMSTFACTORY_H
#define SMSTFACTORY_H

#include "smst.h"

namespace RECTILINEAR_STEINER_TREE {
class SMSTFactory
{
public:
	SMSTFactory() = default;
	virtual ~SMSTFactory() = default;
	virtual SMST* generateSMST() = 0;
};
}

#endif // SMSTFACTORY_H
