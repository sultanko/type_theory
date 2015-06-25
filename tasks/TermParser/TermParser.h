//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_PARSER_H
#define TASKS_PARSER_H

#include "Term.h"

class TermParser
{
private:
    struct State
    {
        tptr term;
        size_t pos;

        State(const tptr &term, size_t pos) : term(term), pos(pos)
        { }

        State(const Term* term, size_t pos) : term(term), pos(pos)
        {}
    };

    static State getTerm(const std::string& str, size_t pos);
    static State getFunction(const std::string& str, size_t pos);
    static State getVariable(const std::string& str, size_t pos);

    static size_t skipSpaces(const std::string& str, size_t pos);


public:
    static tptr parseString(const std::string& str);
};


#endif //TASKS_PARSER_H
