//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_VARIABLE_H
#define TASK1_VARIABLE_H


#include "Expression.h"

class Variable : public Expression
{
private:
    std::string variable;
public:
    virtual std::string toString() const override;

    virtual bool isEqual(const eptr &other) const override;

    Variable(const std::string& str) : variable(str) {}

    virtual std::set<std::string> getFreeVariables() const override;
};


#endif //TASK1_VARIABLE_H
