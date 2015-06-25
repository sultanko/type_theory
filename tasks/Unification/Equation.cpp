//
// Created by sultan on 25.06.15.
//

#include "Equation.h"

std::string Equation::toString() const
{
    return left->toString() + "=" + right->toString();
}

eqptr Equation::substitute(const std::string &oldVar, const tptr &replacement) const
{
    return eqptr(new Equation(left->substitute(oldVar, replacement),
    right->substitute(oldVar, replacement)));
}
