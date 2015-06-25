//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_ABSTRACTION_H
#define TASK1_ABSTRACTION_H


#include "Expression.h"

class Application : public Expression
{
private:
    eptr left;
    eptr right;
public:
    template <typename T1, typename T2>
    Application(T1 l, T2 r) : left(l), right(r)
    {
        strExpr = "(" + left->toString() + " " + right->toString() + ")";
    }

    virtual const std::string & toString() const override;

    virtual bool isEqual(const eptr &other) const override;

    virtual const std::set<std::string> & getFreeVariables() const override;

    const eptr &getLeft() const
    {
        return left;
    }

    const eptr &getRight() const
    {
        return right;
    }

    virtual eptr normalizeSubstitute(const std::string &var, const eptr &subst) const override;

    virtual SubstitutionState sustitute(const std::string &variable, const eptr &expr,
                                        const std::set<std::string> &freeVars) const override;
};


#endif //TASK1_ABSTRACTION_H
