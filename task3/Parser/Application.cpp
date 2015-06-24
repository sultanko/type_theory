//
// Created by sultan on 24.06.15.
//

#include "Application.h"


using std::string;
using std::set;

std::string Application::toString() const
{
    return "(" + left->toString() + " " + right->toString() + ")";
}

bool Application::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(*this))
    {
        const Application * otherA = static_cast<const Application *>(other.get());
        return left->isEqual(otherA->left) && right->isEqual(otherA->right);
    }
    return false;
}

std::set<std::string> Application::getFreeVariables() const
{
    set<string> res = left->getFreeVariables();
    set<string> res2 = right->getFreeVariables();
    res.insert(res2.begin(), res2.end());
    return res;
}

Expression::SubstitutionState Application::sustitute(const std::string &variable, const eptr &expr,
                                                     const std::set<std::string> &freeVars) const
{
    SubstitutionState lstate = left->sustitute(variable, expr, freeVars);
    SubstitutionState rstate = right->sustitute(variable, expr, freeVars);
    return SubstitutionState(
            new Application(lstate.expr, rstate.expr), lstate.used | rstate.used);
}
