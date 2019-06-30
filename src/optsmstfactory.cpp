#include "optsmstfactory.h"
#include "optsmsttimer.h"
#include "optsmst.h"

namespace RECTILINEAR_STEINER_TREE {

OptSMSTFactory::OptSMSTFactory(RecordType type) : SMSTFactory(), recordType(type)
{
}

void OptSMSTFactory::setRecordType(RecordType type)
{
    recordType = type;
}

SMST* OptSMSTFactory::generateSMST()
{
    SMST* smst;
    if (recordType == RECORD)
    {
        smst = new OptSMSTTimer;
    }
    else
    {
        smst = new OptSMST;
    }
    return smst;
}
}
