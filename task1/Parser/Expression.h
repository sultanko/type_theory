//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_EXPRESSION_H
#define TASK1_EXPRESSION_H

#include <string>
#include <iostream>
#include <memory>

class Expression;

typedef std::shared_ptr<const Expression> eptr;

class Expression
{
public:
    virtual std::string toString() const = 0;
    virtual bool isEqual(const eptr& other) const = 0;
    virtual ~Expression() {};

};



#endif //TASK1_EXPRESSION_H
