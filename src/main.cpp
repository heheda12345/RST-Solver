#include <iostream>
#include <string>
#include <windows.h>

#include "lrstfactory.h"
#include "srstfactory.h"
#include "optsmstfactory.h"
#include "primsmstfactory.h"
#include "rstsolver.h"
#include "timerecorder.h"
#include "optsmst.h"
#include "smst.h"

using namespace RECTILINEAR_STEINER_TREE;
using namespace std;

int main()
{
	PrimSMSTFactory f_prim(PrimSMSTFactory::RECORD);
	OptSMSTFactory  f_opt(OptSMSTFactory::RECORD);
	LRSTFactory f_LRST(LRSTFactory::NORECORD);
	SRSTFactory f_SRST(SRSTFactory::NORECORD);
	PointSet ps;
	for (int C = 1; C <= 6; C++)
	{
		freopen((string("../testcase/input") + to_string(C) + string(".in")).c_str(), "r", stdin);
		int n;
		cerr << "Running " << string("../testcase/input") + to_string(C) + string(".in") << "..." << endl;
		cin >> n;
		ps.clear();
		for (int i = 0; i < n; i++)
		{
			Point p;
			cin >> p;
			ps.push_back(p);
		}
		fclose(stdin);

		cerr << "#1 " << "PRIM :" << endl;
		RSTSolver rstSolver(f_prim, f_LRST);
		TimeRecorder::Instance()->clear();
		rstSolver.run(ps);
		cerr << "value : " << rstSolver.getLayout().value() << endl;
		cerr << "time : " << TimeRecorder::Instance()->getTime() << endl;

		cerr << "#2 " << "OPT :" << endl;
		rstSolver.setSMSTFactory(f_opt);
		rstSolver.setRSTFactory(f_LRST);
		TimeRecorder::Instance()->clear();
		rstSolver.run(ps);
		cerr << "value : " << rstSolver.getLayout().value() << endl;
		cerr << "time : " << TimeRecorder::Instance()->getTime() << endl;
	}
	return 0;
}
