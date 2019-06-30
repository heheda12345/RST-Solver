#ifndef PRIMSMST_H
#define PRIMSMST_H

#include "smst.h"

namespace RECTILINEAR_STEINER_TREE {
class PrimSMST : public SMST
{
public:
	PrimSMST() = default;
	virtual ~PrimSMST() = default;
	void run(PointSet&, MST&);
};
}
#endif // PRIMSMST_H
