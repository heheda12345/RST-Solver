#ifndef RSTSOLVER_H
#define RSTSOLVER_H

#include "rstfactory.h"
#include "smstfactory.h"

namespace RECTILINEAR_STEINER_TREE {
class SMSTFactory;
class RSTFactory;
class MST;
class Layout;

class RSTSolver
{
public:
    RSTSolver(SMSTFactory &s, RSTFactory &r);
    virtual ~RSTSolver() = default;
    RSTSolver(const RSTSolver& other) = delete;
    RSTSolver& operator=(const RSTSolver& other) = delete;
    void run(PointSet&);
    const Layout& getLayout();
    void setSMSTFactory(SMSTFactory& s);
    void setRSTFactory(RSTFactory &r);

protected:
    SMSTFactory *smstFactory;
    RSTFactory *rstFactory;
    MST mst;
    Layout layout;
};
}

#endif // RSTSOLVER_H
