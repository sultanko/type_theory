//
// Created by sultan on 25.06.15.
//

#include "TermParser.h"
#include "TermVariable.h"
#include "Function.h"

using std::string;
using std::vector;

tptr TermParser::parseString(const std::string &str)
{
    return getTerm(str, skipSpaces(str, 0)).term;
}

TermParser::State TermParser::getTerm(const std::string &str, size_t pos)
{
    if (str[pos] >= 'a' && str[pos] <= 'h')
    {
        return getFunction(str, pos);
    }
    else
    {
        return getVariable(str, pos);
    }
}

TermParser::State TermParser::getFunction(const std::string &str, size_t pos)
{
    size_t oldPos = pos;
    while (pos < str.size() && (isalnum(str[pos]) || str[pos] == '\''))
    {
        pos++;
    }
    string fName(str, oldPos, pos - oldPos);
    pos = skipSpaces(str, pos);
    if (str[pos] != '(')
    {
        throw std::runtime_error("open brace expected");
    }
    pos = skipSpaces(str, pos + 1);
    vector<tptr> terms;
    while (str[pos] != ')')
    {
        State nextTerm = getTerm(str, pos);
        terms.push_back(nextTerm.term);
        pos = nextTerm.pos;
        if (str[pos] == ',')
        {
            pos = skipSpaces(str, pos + 1);
        }
    }
    pos = skipSpaces(str, pos + 1);
    return State(new Function(fName, terms), pos);
}

TermParser::State TermParser::getVariable(const std::string &str, size_t pos)
{
    if (str[pos] < 'i' || str[pos] > 'z')
    {
        throw std::runtime_error("error parsing variable");
    }
    size_t oldPos = pos;
    while (pos < str.size() && (isalnum(str[pos]) || str[pos] == '\''))
    {
        pos++;
    }
    tptr var(new TermVariable(str.substr(oldPos, pos - oldPos)));
    return State(var, skipSpaces(str, pos));
}

size_t TermParser::skipSpaces(const std::string &str, size_t pos)
{
    while (pos < str.size() && (str[pos] == ' ' || str[pos] == '\n'))
    {
        pos++;
    }
    return pos;
}
