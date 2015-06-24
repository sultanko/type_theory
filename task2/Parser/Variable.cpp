//
// Created by sultan on 24.06.15.
//

#include "Variable.h"

using std::string;
using std::set;

std::string Variable::toString() const
{
    return variable;
}

bool Variable::isEqual(const eptr &other) const
{
    return other->toString() == variable;
}

std::set<std::string> Variable::getFreeVariables() const
{
    set<string> now;
    now.insert(variable);
    return now;
}
