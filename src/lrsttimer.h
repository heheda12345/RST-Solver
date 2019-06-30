#ifndef LRSTTIMER_H
#define LRSTTIMER_H

#include "LRST.h"

namespace RECTILINEAR_STEINER_TREE {
class LRSTTimer : public LRST
{
public:
	LRSTTimer() = default;
	virtual ~LRSTTimer() = default;
	void run(MST&, Layout&) override;
};
}

#endif // LRSTTIMER_H
