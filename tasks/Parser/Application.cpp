//
// Created by sultan on 24.06.15.
//

#include "Application.h"


using std::string;
using std::set;

const string & Application::toString() const
{
//    return "(" + left->toString() + " " + right->toString() + ")";
    return strExpr;
}

bool Application::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(Application))
    {
        const Application * otherA = static_cast<const Application *>(other.get());
        return left->isEqual(otherA->left) && right->isEqual(otherA->right);
    }
    return false;
}

const set<string> & Application::getFreeVariables() const
{
    if (freeVars->wasComputed)
    {
        return freeVars->freeVars;
    }
    set<string> res = left->getFreeVariables();
    set<string> res2 = right->getFreeVariables();
    res.insert(res2.begin(), res2.end());
    freeVars->setComputed(res);
    return freeVars->getFreeVars();
}

Expression::SubstitutionState Application::sustitute(const std::string &variable, const eptr &expr,
                                                     const std::set<std::string> &freeVars) const
{
    SubstitutionState lstate = left->sustitute(variable, expr, freeVars);
    SubstitutionState rstate = right->sustitute(variable, expr, freeVars);
    return SubstitutionState(
            new Application(lstate.expr, rstate.expr), lstate.used | rstate.used);
}

eptr Application::normalizeSubstitute(const string &var, const eptr &subst) const
{
    return eptr(new Application(left->normalizeSubstitute(var, subst),
    right->normalizeSubstitute(var, subst)));
}
