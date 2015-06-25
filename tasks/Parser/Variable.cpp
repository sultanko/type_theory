//
// Created by sultan on 24.06.15.
//

#include "Variable.h"

using std::string;
using std::set;

const string & Variable::toString() const
{
    return variable;
}

bool Variable::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(Variable))
    {
        const Variable* otherVar = (const Variable*)other.get();
        return otherVar->variable == variable;
    }
    return false;
}

const set<string> & Variable::getFreeVariables() const
{
    return freeVars->getFreeVars();
}

Expression::SubstitutionState Variable::sustitute(const std::string &variable, const eptr &expr,
                                                  const std::set<std::string> &freeVars) const
{
    if (this->variable == variable)
    {
        return SubstitutionState(expr, true);
    }
    else
    {
        return SubstitutionState(new Variable(this->variable), false);
    }
}

eptr Variable::normalizeSubstitute(const string &var, const eptr &subst) const
{
    if (variable == var)
    {
        return subst;
    }
    else
    {
        return eptr(new Variable(variable));
    }
}
