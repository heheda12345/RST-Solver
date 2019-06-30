#ifndef OPTTIMERFACTORY_H
#define OPTTIMERFACTORY_H

#include "smstfactory.h"

namespace RECTILINEAR_STEINER_TREE {

class OptSMSTFactory : public SMSTFactory
{
public:
	enum RecordType { RECORD, NORECORD };
	OptSMSTFactory(RecordType);
	virtual ~OptSMSTFactory() = default;
	SMST* generateSMST();
	void setRecordType(RecordType);

private:
	RecordType recordType;
};

}

#endif // OPTTIMERFACTORY_H
