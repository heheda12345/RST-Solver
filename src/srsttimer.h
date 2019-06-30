#ifndef SRSTTIMER_H
#define SRSTTIMER_H

#include "srst.h"

namespace RECTILINEAR_STEINER_TREE {
class SRSTTimer : public SRST
{
public:
	SRSTTimer() = default;
	virtual ~SRSTTimer() = default;
	void run(MST&, Layout&) override;
};
}

#endif // SRSTTIMER_H
