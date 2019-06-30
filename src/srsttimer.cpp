#include "srsttimer.h"
#include "timerecorder.h"

namespace RECTILINEAR_STEINER_TREE {
class TimeRecorder;

void SRSTTimer::run(MST& mst, Layout& layout)
{
	TimeRecorder::Instance()->start();
	SRST::run(mst, layout);
	TimeRecorder::Instance()->stop();
}
}
