#ifndef PRIMSMSTTIMER_H
#define PRIMSMSTTIMER_H

#include "primsmst.h"

namespace RECTILINEAR_STEINER_TREE {
class PrimSMSTTimer : public PrimSMST
{
public:
	PrimSMSTTimer() = default;
	virtual ~PrimSMSTTimer() = default;
	void run(PointSet&, MST&);
};
}

#endif // PRIMSMSTTIMER_H
