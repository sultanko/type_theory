//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_PARSER_H
#define TASK1_PARSER_H

#include "Expression.h"

class Parser
{
private:
    struct Result
    {
        eptr expr;
        size_t pos;

        template <typename T>
        Result(T ptr, size_t pos) : expr(ptr), pos(pos) {}
    };
    static Result getVariable(const std::string& str, size_t curPos);
    static Result getAtom(const std::string& str, size_t curPos);
    static Result getApplication(const std::string& str, size_t curPos);
    static Result getAbstraction(const std::string& str, size_t curPos);
    static Result getExpression(const std::string& str, size_t curPos);
    static size_t skipSpaces(const std::string& str, size_t curPos);
public:
    static eptr parseString(const std::string& str);
};


#endif //TASK1_PARSER_H
