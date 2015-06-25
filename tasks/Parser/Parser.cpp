//
// Created by sultan on 24.06.15.
//

#include "Parser.h"
#include "Abstraction.h"
#include "Application.h"
#include "../TermParser/TermParser.h"

using std::string;


eptr Parser::parseString(const std::string &str)
{
    return getExpression(str, skipSpaces(str, 0)).expr;
}

size_t Parser::skipSpaces(const std::string &str, size_t curPos)
{
    while (curPos < str.size() &&
            (str[curPos] == ' ' || str[curPos] == '\n' || str[curPos] == '\t'))
    {
        ++curPos;
    }
    return curPos;
}

Parser::Result Parser::getExpression(const std::string &str, size_t curPos)
{
    if (str[curPos] == '\\')
    {
        return getAbstraction(str, curPos);
    }
    Result result = getApplication(str, curPos);
    curPos = result.pos;
    if (str[curPos] == '\\')
    {
        Result abstr = getAbstraction(str, curPos);
        result.expr.reset(new Application(result.expr, abstr.expr));
        result.pos = abstr.pos;
    }
    result.pos = skipSpaces(str, result.pos);
    return result;
}

Parser::Result Parser::getAbstraction(const std::string &str, size_t curPos)
{
    if (str[curPos] != '\\')
    {
        string error("lamda expected at");
        error.append(std::to_string(curPos)).append(" but was ")
                .append(std::to_string(str[curPos]));
        throw std::runtime_error(error);
    }
    Result variable = getVariable(str, skipSpaces(str, curPos + 1));
    curPos = variable.pos;
    if (str[curPos] != '.')
    {
        string error("dot expected at");
        error.append(std::to_string(curPos)).append(" but was ")
                .append(std::to_string(str[curPos]));
        throw std::runtime_error(error);
    }
    curPos = skipSpaces(str, curPos + 1);
    Result result = getExpression(str, curPos);
    result.expr.reset(new Abstraction(variable.expr, result.expr));
    return result;
}

Parser::Result Parser::getApplication(const std::string &str, size_t curPos)
{
    Result result = getAtom(str, curPos);
    curPos = skipSpaces(str, result.pos);
    while (curPos < str.size() &&
            (str[curPos] == '(' || isalpha(str[curPos])))
    {
        Result atom = getAtom(str, curPos);
        result.expr.reset(new Application(result.expr, atom.expr));
        curPos = skipSpaces(str, atom.pos);
    }
    result.pos = skipSpaces(str, curPos);
    return result;
}

Parser::Result Parser::getAtom(const std::string &str, size_t curPos)
{
    if (str[curPos] == '(')
    {
        Result result = getExpression(str, skipSpaces(str, curPos + 1));
        if (str[result.pos] != ')')
        {
            throw std::runtime_error("expected )");
        }
        result.pos = skipSpaces(str, result.pos + 1);
        return result;
    }
    return getVariable(str, curPos);
}

Parser::Result Parser::getVariable(const std::string &str, size_t curPos)
{
    size_t oldPos = curPos;
    while (curPos < str.size() &&
            (isalnum(str[curPos]) || str[curPos] == '\''))
    {
        curPos++;
    }
    string name(str, oldPos, curPos - oldPos);
    return Result(new Variable(name), skipSpaces(str, curPos));
}

