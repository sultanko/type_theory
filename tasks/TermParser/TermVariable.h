//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_TERMVARIABLE_H
#define TASKS_TERMVARIABLE_H


#include "Term.h"

class TermVariable : public Term
{
private:
    const std::string varName;
    std::set<std::string> variables;
public:
    TermVariable(const std::string& name) : varName(name)
    {
        variables.insert(varName);
    }

    virtual bool isEqual(const tptr &other) const override;

    virtual tptr substitute(const std::string &oldVar, const tptr &replacement) const override;

    virtual const std::set<std::string>& getVariables() const override;

    virtual std::string toTypeString() const override;

    virtual const std::string & toString() const override;
};


#endif //TASKS_TERMVARIABLE_H
