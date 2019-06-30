#include "lrsttimer.h"
#include "timerecorder.h"

namespace RECTILINEAR_STEINER_TREE {

class TimeRecorder;

void LRSTTimer::run(MST& mst, Layout& layout)
{
	TimeRecorder::Instance()->start();
	LRST::run(mst, layout);
	TimeRecorder::Instance()->stop();
}
}
