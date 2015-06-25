//
// Created by sultan on 24.06.15.
//

#include "Normalization.h"
#include "../Parser/Variable.h"
#include "../Parser/Abstraction.h"
#include "../Parser/Application.h"


std::unordered_map<eptr, eptr, Expression_hash_fn, Expression_equals_fn> Normalization::headMem;
std::unordered_map<eptr, eptr, Expression_hash_fn, Expression_equals_fn> Normalization::mem;

eptr Normalization::normalize(const eptr &expr)
{
    if (mem.find(expr) != mem.end())
    {
        return mem[expr];
    }
    if (typeid(*expr.get()) == typeid(Variable))
    {
        return expr;
    }
    else if (typeid(*expr.get()) == typeid(Abstraction))
    {
        const Abstraction* abstraction = (const Abstraction*)expr.get();
        eptr normAbs(new Abstraction(abstraction->getVariable(), normalize(abstraction->getExpr())));
        mem[expr] = normAbs;
    }
    else
    {
        const Application* application = (const Application*)expr.get();
        const eptr& left = application->getLeft();
        const eptr& right = application->getRight();
        eptr headNormLeft = headNormalize(left);
        if (typeid(*headNormLeft.get()) == typeid(Abstraction))
        {
            const Abstraction* leftAbs = (const Abstraction*)headNormLeft.get();
            eptr subst = leftAbs->getExpr()->normalizeSubstitute(leftAbs->getVariable()->toString(), right);
            eptr normSubst = normalize(subst);
            mem[expr] = normSubst;
        }
        else
        {
            eptr result(new Application(normalize(headNormLeft), normalize(right)));
            mem[expr] = result;
        }
    }
    return mem[expr];
}

eptr Normalization::headNormalize(const eptr &expr)
{
    if (headMem.find(expr) != headMem.end())
    {
        return headMem[expr];
    }
    if (typeid(*expr.get()) == typeid(Variable))
    {
        return expr;
    }
    else if (typeid(*expr.get()) == typeid(Abstraction))
    {
        const Abstraction* abstraction = (const Abstraction*)expr.get();
        eptr normAbs(new Abstraction(abstraction->getVariable(), headNormalize(abstraction->getExpr())));
        headMem[expr] = normAbs;
    }
    else
    {
        const Application* application = (const Application*)expr.get();
        eptr left = application->getLeft();
        eptr right = application->getRight();
        eptr headNormLeft = headNormalize(left);
        if (typeid(*headNormLeft.get()) == typeid(Abstraction))
        {
            const Abstraction* leftAbs = (const Abstraction*)headNormLeft.get();
            eptr subst = leftAbs->getExpr()->normalizeSubstitute(leftAbs->getVariable()->toString(), right);
            eptr normSubst = headNormalize(subst);
            headMem[expr] = normSubst;
        }
        else
        {
            eptr result(new Application(headNormLeft, right));
            headMem[expr] = result;
        }
    }
    return headMem[expr];
}
