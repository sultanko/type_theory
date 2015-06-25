//
// Created by sultan on 25.06.15.
//

#include "Unification.h"
#include "../TermParser/TermVariable.h"
#include "../TermParser/Function.h"

using std::vector;
using std::string;

void Unification::addEquation(const eqptr &equation)
{
    equations.push_back(equation);
}

void Unification::clear()
{
    equations.clear();
}

std::vector<eqptr> Unification::solveSystem()
{
    vector<eqptr> solution;
    while (!equations.empty())
    {
        eqptr cur = equations.back();
        equations.pop_back();
        const tptr& left = cur->getLeft();
        const tptr& right = cur->getRight();
        if (typeid(*left.get()) == typeid(TermVariable)
                && right->getVariables().find(left->toString()) == right->getVariables().end()
                )
        {
            const std::string& varName = left->toString();
            solution = doSubstitute(solution, varName, right);
            equations = doSubstitute(equations, varName, right);
            solution.emplace_back(new Equation(left, right));
            continue;
        }
        else if (typeid(*right.get()) == typeid(TermVariable)
                 && left->getVariables().find(right->toString()) == left->getVariables().end()
                )
        {
            const std::string& varName = right->toString();
            solution = doSubstitute(solution, varName, left);
            equations = doSubstitute(equations, varName, left);
            solution.emplace_back(new Equation(right, left));
            continue;
        }
        else if (typeid(*left.get()) == typeid(Function)
            && typeid(*right.get()) == typeid(Function)
                )
        {
            const Function *leftF = (const Function *) left.get();
            const Function *rightF = (const Function *) right.get();
            const vector<tptr> &leftTerms = leftF->getTerms();
            const vector<tptr> &rightTerms = rightF->getTerms();
            if (leftF->getFunctionName() != rightF->getFunctionName()
                || leftTerms.size() != rightTerms.size())
            {
                throw UnificationException();
            }
            for (size_t i = 0; i < leftTerms.size(); ++i)
            {
                equations.emplace_back(new Equation(leftTerms[i], rightTerms[i]));
            }
            continue;
        }
        else if (typeid(*left.get()) == typeid(TermVariable)
                 && typeid(*right.get()) == typeid(TermVariable)
                && left->toString() == right->toString()
        )
        {
            continue;
        }
        throw UnificationException();
    }
    return solution;
}

const char *UnificationException::what() const _GLIBCXX_NOEXCEPT
{
    return "Система не разрешима";
}

std::vector<eqptr> Unification::doSubstitute(const std::vector<eqptr> &vec, const std::string &oldVar,
                                             const tptr &replacement) const
{
    vector<eqptr> res;
    for (auto item : vec)
    {
        res.push_back(item->substitute(oldVar, replacement));
    }
    return res;
}

void Unification::addEquation(const Equation *equation)
{
    equations.emplace_back(equation);
}
