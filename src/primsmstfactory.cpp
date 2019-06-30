#include "primsmstfactory.h"
#include "primsmsttimer.h"
#include "primsmst.h"

namespace RECTILINEAR_STEINER_TREE {

PrimSMSTFactory::PrimSMSTFactory(RecordType type) : SMSTFactory(), recordType(type)
{
}

void PrimSMSTFactory::setRecordType(RecordType type)
{
    recordType = type;
}

SMST* PrimSMSTFactory::generateSMST()
{
    SMST* smst;
    if (recordType == RECORD)
    {
        smst = new PrimSMSTTimer;
    }
    else
    {
        smst = new PrimSMST;
    }
    return smst;
}
}
