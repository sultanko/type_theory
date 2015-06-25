//
// Created by sultan on 25.06.15.
//

#include "Function.h"

using std::vector;
using std::string;

Function::Function(const std::string& name, const std::vector<tptr>& terms)
        : functionName(name), terms(terms)
{
    stringExpr = functionName + '(';
    for (size_t i = 0; i < terms.size() - 1; ++i)
    {
        stringExpr += terms[i]->toString() + ',';
    }
    if (!terms.empty())
    {
        stringExpr += terms.back()->toString();
    }
    for (auto term : terms)
    {
        auto varSet = term->getVariables();
        variables.insert(varSet.begin(), varSet.end());
    }
    stringExpr += ')';
}

bool Function::isEqual(const tptr &other) const
{
    if (typeid(*other.get()) == typeid(Function))
    {
        const Function* otherF = (const Function*)other.get();
        if (otherF->functionName != functionName
                || otherF->terms.size() != terms.size())
        {
            return false;
        }
        for (size_t i = 0; i < terms.size(); ++i)
        {
            if (terms[i] != otherF->terms[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

const std::string &Function::toString() const
{
    return stringExpr;
}

tptr Function::substitute(const std::string &oldVar, const tptr &replacement) const
{
    vector<tptr> newTerms;
    for (auto term : terms)
    {
        newTerms.push_back(term->substitute(oldVar, replacement));
    }
    return tptr(new Function(functionName, newTerms));
}

const std::set<std::string>& Function::getVariables() const
{
    return variables;
}

std::string Function::toTypeString() const
{
    if (terms.size() != 2)
    {
        throw std::runtime_error("invalid function to arrow");
    }
    return "(" + terms[0]->toTypeString() + "->" + terms[1]->toTypeString() + ")";
}
