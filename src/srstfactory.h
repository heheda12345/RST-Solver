#ifndef SRSTTIMERFACTORY_H
#define SRSTTIMERFACTORY_H

#include "rstfactory.h"

namespace RECTILINEAR_STEINER_TREE {

class SRSTFactory : public RSTFactory
{
public:
	enum RecordType { RECORD, NORECORD };
	SRSTFactory(RecordType);
	virtual ~SRSTFactory() = default;
	RST* generateRST() override;
	void setRecordType(RecordType);

private:
	RecordType recordType;
};

}

#endif // SRSTTIMERFACTORY_H
