#include "rstsolver.h"

namespace RECTILINEAR_STEINER_TREE {
RSTSolver::RSTSolver(SMSTFactory &s, RSTFactory &r) : smstFactory(&s), rstFactory(&r)
{
}

void RSTSolver::run(PointSet& ps)
{
    layout = Layout();
    SMST *s = smstFactory->generateSMST();
    s->run(ps, mst);
    RST *r = rstFactory->generateRST();
    r->run(mst, layout);
    delete s;
    delete r;
}

const Layout& RSTSolver::getLayout()
{
    return layout;
}

void RSTSolver::setSMSTFactory(SMSTFactory& s)
{
    smstFactory = &s;
}
void RSTSolver::setRSTFactory(RSTFactory &r)
{
    rstFactory = &r;
}

}
