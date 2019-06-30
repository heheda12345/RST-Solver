#include "optsmsttimer.h"
#include "timerecorder.h"

namespace RECTILINEAR_STEINER_TREE {
class TimeRecorder;

void OptSMSTTimer::run(PointSet& ps, MST& mst)
{
	TimeRecorder::Instance()->start();
	OptSMST::run(ps, mst);
	TimeRecorder::Instance()->stop();
}
}
