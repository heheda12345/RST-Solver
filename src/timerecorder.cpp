#include <sys/time.h>
#include <sys/timeb.h>

#include "TimeRecorder.h"

namespace RECTILINEAR_STEINER_TREE {
TimeRecorder* TimeRecorder::instance_ = 0;

TimeRecorder* TimeRecorder::Instance()
{
	if (instance_ == 0)
		instance_ = new TimeRecorder();
	return instance_;
}
void TimeRecorder::clear()
{
	QueryPerformanceFrequency(&winFreq);
	sumTime = 0;
}

void TimeRecorder::start()
{
	QueryPerformanceCounter(&winStart);
}

void TimeRecorder::stop()
{
	LARGE_INTEGER winEnd;
	QueryPerformanceCounter(&winEnd);
	sumTime += (double)(winEnd.QuadPart - winStart.QuadPart) / (double)winFreq.QuadPart;
}

double TimeRecorder::getTime()const
{
	return sumTime;
}

}
