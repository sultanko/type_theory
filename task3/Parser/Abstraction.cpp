//
// Created by sultan on 24.06.15.
//

#include "Abstraction.h"

using std::string;
using std::set;

std::string Abstraction::toString() const
{
    return "(\\" + variable->toString() + ". " + expr->toString() + ")";
}

bool Abstraction::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(*this))
    {
        const Abstraction * otherA = static_cast<const Abstraction *>(other.get());
        return variable->isEqual(otherA->variable) && expr->isEqual(otherA->expr);
    }
    return false;
}

std::set<std::string> Abstraction::getFreeVariables() const
{
    set<string> res = expr->getFreeVariables();
    res.erase(variable->toString());
    return res;
}

Expression::SubstitutionState Abstraction::sustitute(const std::string &variable, const eptr &expr,
                                                     const std::set<std::string> &freeVars) const
{
    if (this->variable->toString() == variable)
    {
        return SubstitutionState(new Abstraction(this->variable, this->expr), false);
    }
    SubstitutionState res = this->expr->sustitute(variable, expr, freeVars);
    if (res.used)
    {
        if (freeVars.find(this->variable->toString()) != freeVars.end())
        {
            throw SubtitutionException(this->variable->toString());
        }
    }
    return SubstitutionState(new Abstraction(this->variable, res.expr), res.used);
}
