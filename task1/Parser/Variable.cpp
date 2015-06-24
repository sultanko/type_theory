//
// Created by sultan on 24.06.15.
//

#include "Variable.h"

std::string Variable::toString() const
{
    return variable;
}

bool Variable::isEqual(const eptr &other) const
{
    return other->toString() == variable;
}
