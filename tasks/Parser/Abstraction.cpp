//
// Created by sultan on 24.06.15.
//

#include "Abstraction.h"

using std::string;
using std::set;

const string & Abstraction::toString() const
{
//    return "(\\" + variable->toString() + ". " + expr->toString() + ")";
    return strExpr;
}

bool Abstraction::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(Abstraction))
    {
        const Abstraction * otherA = static_cast<const Abstraction *>(other.get());
        return variable->isEqual(otherA->variable) && expr->isEqual(otherA->expr);
    }
    return false;
}

const set<string> & Abstraction::getFreeVariables() const
{
    if (freeVars->wasComputed)
    {
        return freeVars->freeVars;
    }
    set<string> res = expr->getFreeVariables();
    res.erase(variable->toString());
    freeVars->setComputed(res);
    return freeVars->getFreeVars();
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

eptr Abstraction::normalizeSubstitute(const string &var, const eptr &subst) const
{
    const set<string>& freeExprVars = expr->getFreeVariables();
    if (variable->toString() == var || freeExprVars.find(var) == freeExprVars.end())
    {
        return eptr(new Abstraction(variable, expr));
    }
    const set<string>& freeSubstVars = subst->getFreeVariables();
    if (freeSubstVars.find(variable->toString()) == freeSubstVars.end())
    {
        return eptr(new Abstraction(variable, expr->normalizeSubstitute(var, subst)));
    }
    set<string> allVars(freeExprVars);
    allVars.insert(freeSubstVars.begin(), freeSubstVars.end());
    string varName = "z";
    while (allVars.find(varName) != allVars.end())
    {
        varName.append("'");
    }
    eptr newVar(new Variable(varName));
    eptr substExpr = expr->normalizeSubstitute(variable->toString(), newVar);
    return eptr(new Abstraction(newVar, substExpr->normalizeSubstitute(var, subst)));
}
