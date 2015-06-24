//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_EXPRESSION_H
#define TASK1_EXPRESSION_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>

class Expression;

typedef std::shared_ptr<const Expression> eptr;

class Expression
{
public:
    struct SubstitutionState
    {
        eptr expr;
        bool used;
        template <typename T>
        SubstitutionState(T expr, bool used) : expr(expr), used(used) {}
    };
    struct SubtitutionException : public std::exception
    {
        std::string varName;
        SubtitutionException(const std::string& var)
                : varName("Нет свободы для подстановки " + var) {}
        const char *what() const _GLIBCXX_USE_NOEXCEPT override;
    };
    virtual std::string toString() const = 0;
    virtual bool isEqual(const eptr& other) const = 0;
    virtual std::set<std::string> getFreeVariables() const = 0;
    virtual SubstitutionState sustitute(
            const std::string& variable,
            const eptr& expr,
            const std::set<std::string>& freeVars) const = 0;
    virtual ~Expression() {};

};



#endif //TASK1_EXPRESSION_H
