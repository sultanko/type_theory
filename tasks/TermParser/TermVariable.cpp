//
// Created by sultan on 25.06.15.
//

#include "TermVariable.h"

bool TermVariable::isEqual(const tptr &other) const
{
    if (typeid(*other.get()) == typeid(TermVariable))
    {
        return ((const TermVariable*)other.get())->varName == varName;
    }
    return false;
}

const std::string & TermVariable::toString() const
{
    return varName;
}

tptr TermVariable::substitute(const std::string &oldVar, const tptr &replacement) const
{
    if (varName == oldVar)
    {
        return replacement;
    }
    else
    {
        return tptr(new TermVariable(varName));
    }
}

const std::set<std::string>& TermVariable::getVariables() const
{
    return variables;
}

std::string TermVariable::toTypeString() const
{
    return varName;
}
