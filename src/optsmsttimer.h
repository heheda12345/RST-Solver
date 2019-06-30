#ifndef OPTSMSTTIMER_H
#define OPTSMSTTIMER_H

#include "optsmst.h"

namespace RECTILINEAR_STEINER_TREE {
class OptSMSTTimer : public OptSMST
{
public:
	OptSMSTTimer() = default;
	virtual ~OptSMSTTimer() = default;
	void run(PointSet&, MST&);
};
}

#endif // OPTSMSTTIMER_H
