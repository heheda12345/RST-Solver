#include "srstfactory.h"
#include "srsttimer.h"
#include "srst.h"

namespace RECTILINEAR_STEINER_TREE {

SRSTFactory::SRSTFactory(RecordType type) : RSTFactory(), recordType(type)
{
}

void SRSTFactory::setRecordType(RecordType type)
{
    recordType = type;
}

RST* SRSTFactory::generateRST()
{
    RST* rst;
    if (recordType == RECORD)
    {
        rst = new SRSTTimer;
    }
    else
    {
        rst = new SRST;
    }
    return rst;
}
}
