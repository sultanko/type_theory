//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_FUNCTION_H
#define TASKS_FUNCTION_H


#include "Term.h"

class Function : public Term
{
private:
    const std::string functionName;
    const std::vector<tptr> terms;
    std::string stringExpr;
    std::set<std::string> variables;
public:
    Function(const std::string& name, const std::vector<tptr>& terms);


    virtual bool isEqual(const tptr &other) const override;

    virtual tptr substitute(const std::string &oldVar, const tptr &replacement) const override;

    virtual const std::string &toString() const override;

    virtual const std::set<std::string>& getVariables() const override;

    const std::vector<tptr> &getTerms() const
    {
        return terms;
    }

    const std::string &getFunctionName() const
    {
        return functionName;
    }

};


#endif //TASKS_FUNCTION_H
