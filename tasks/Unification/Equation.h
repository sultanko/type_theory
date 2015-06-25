//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_EQUATION_H
#define TASKS_EQUATION_H

#include "../TermParser/Term.h"

class Equation;

typedef std::shared_ptr<const Equation> eqptr;

class Equation
{
private:
    const tptr left;
    const tptr right;

public:
    Equation(const tptr &left, const tptr &right) : left(left), right(right)
    { }

    std::string toString() const;

    const tptr &getLeft() const
    {
        return left;
    }

    const tptr &getRight() const
    {
        return right;
    }

    eqptr substitute(const std::string& oldVar, const tptr& replacement) const;
};


#endif //TASKS_EQUATION_H
