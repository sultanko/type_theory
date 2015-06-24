//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_APPLICATION_H
#define TASK1_APPLICATION_H


#include "Expression.h"
#include "Variable.h"

class Abstraction : public Expression
{
private:
    eptr variable;
    eptr expr;
public:
    template <typename T1, typename T2>
    Abstraction(T1 var, T2 r) : variable(var), expr(r) { initializeHash(); }

    template <typename T>
    Abstraction(std::string var, T expr) : variable(new Variable(var)), expr(expr) { initializeHash(); }


    virtual std::string toString() const override;

    virtual bool isEqual(const eptr &other) const override;

    virtual std::set<std::string> getFreeVariables() const override;

    const eptr &getVariable() const
    {
        return variable;
    }

    const eptr &getExpr() const
    {
        return expr;
    }

    virtual SubstitutionState sustitute(const std::string &variable, const eptr &expr,
                                        const std::set<std::string> &freeVars) const override;

    virtual eptr normalizeSubstitute(const eptr &var, const eptr &subst) const override;
};


#endif //TASK1_APPLICATION_H
