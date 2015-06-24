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
    Abstraction(T1 l, T2 r) : variable(l), expr(r) {}

    template <typename T>
    Abstraction(std::string var, T expr) : variable(new Variable(var)), expr(expr) {}


    virtual std::string toString() const override;

    virtual bool isEqual(const eptr &other) const override;
};


#endif //TASK1_APPLICATION_H
