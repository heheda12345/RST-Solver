#ifndef __TIMERECORDER_H__
#define __TIMERECORDER_H__

#include <windows.h>
namespace RECTILINEAR_STEINER_TREE {
class TimeRecorder
{
public:
	static TimeRecorder* Instance();
	void clear();
	void start();
	void stop();
	double getTime()const;	//second

private:
	TimeRecorder() {}
	TimeRecorder(const TimeRecorder&); //avoid copy constructor
	TimeRecorder& operator=(const TimeRecorder&); //avoid self-assignment
	~TimeRecorder();
	static TimeRecorder* instance_;

	LARGE_INTEGER winFreq;
	LARGE_INTEGER winStart;
	double sumTime;
};

}

#endif // __TIMERECORDER_H__
