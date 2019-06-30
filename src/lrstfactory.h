#ifndef LRSTTIMERFACTORY_H
#define LRSTTIMERFACTORY_H

#include "rstfactory.h"

namespace RECTILINEAR_STEINER_TREE {

class LRSTFactory : public RSTFactory
{
public:
	enum RecordType { RECORD, NORECORD };
	LRSTFactory(RecordType);
	virtual ~LRSTFactory() = default;
	RST* generateRST() override;
	void setRecordType(RecordType);

private:
	RecordType recordType;
};

}

#endif // LRSTTIMERFACTORY_H
