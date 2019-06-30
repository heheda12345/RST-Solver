#ifndef PRIMTIMERFACTORY_H
#define PRIMTIMERFACTORY_H

#include "smstfactory.h"
#include "primsmsttimer.h"

namespace RECTILINEAR_STEINER_TREE {

class PrimSMSTFactory : public SMSTFactory
{
public:
	enum RecordType { RECORD, NORECORD };
	PrimSMSTFactory(RecordType);
	virtual ~PrimSMSTFactory() = default;
	SMST* generateSMST();
	void setRecordType(RecordType);

private:
	RecordType recordType;
};

}

#endif // PRIMTIMERFACTORY_H
