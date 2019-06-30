#include "lrstfactory.h"
#include "lrsttimer.h"
#include "lrst.h"

namespace RECTILINEAR_STEINER_TREE {

LRSTFactory::LRSTFactory(RecordType type) : RSTFactory(), recordType(type)
{
}

void LRSTFactory::setRecordType(RecordType type)
{
    recordType = type;
}

RST* LRSTFactory::generateRST()
{
    RST* rst;
    if (recordType == RECORD)
    {
        rst = new LRSTTimer;
    }
    else
    {
        rst = new LRST;
    }
    return rst;
}
}
