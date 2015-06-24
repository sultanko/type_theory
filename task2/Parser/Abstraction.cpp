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
