#include "primsmsttimer.h"
#include "timerecorder.h"

namespace RECTILINEAR_STEINER_TREE {
class TimeRecorder;

void PrimSMSTTimer::run(PointSet& ps, MST& mst)
{
	TimeRecorder::Instance()->start();
	PrimSMST::run(ps, mst);
	TimeRecorder::Instance()->stop();
}
}
