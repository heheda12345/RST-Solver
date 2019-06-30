#ifndef OPTSMST_H
#define OPTSMST_H

#include "smst.h"

namespace RECTILINEAR_STEINER_TREE {
class OptSMST : public SMST
{
public:
	OptSMST() = default;
	virtual ~OptSMST() = default;
	void run(PointSet&, MST&);
};
}

#endif // OPTSMST_H
