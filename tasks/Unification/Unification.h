//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_UNIFICATION_H
#define TASKS_UNIFICATION_H

#include "Equation.h"
#include <deque>

struct UnificationException : public std::exception
{
    virtual const char *what() const _GLIBCXX_NOEXCEPT override;
};

class Unification
{
private:
    std::vector<eqptr> equations;

    std::vector<eqptr> doSubstitute(const std::vector<eqptr> &vec, const std::string &oldVar,
                                                 const tptr &replacement) const;
public:
    void addEquation(const eqptr& equation);
    void addEquation(const Equation* equation);
    void clear();
    std::vector<eqptr> solveSystem();
};


#endif //TASKS_UNIFICATION_H
