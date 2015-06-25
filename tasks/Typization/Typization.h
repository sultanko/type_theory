//
// Created by sultan on 26.06.15.
//

#ifndef TASKS_TYPIZATION_H
#define TASKS_TYPIZATION_H

#include "../Unification/Unification.h"
#include "../Parser/Parser.h"

class Typization
{
private:
    int variableTypeCounter;
    Unification unificator;
    std::unordered_map<std::string, int> absVars;
    std::unordered_map<std::string, int> context;



    static bool contains(const std::unordered_map<std::string, int>& container, const std::string& item);
    tptr createNewVar();
    tptr createNewVar(int i);
    tptr createTypeArrow(const tptr& l, const tptr& r);
    tptr createTypeArrow(int l, int r);

public:

    Typization()
        : variableTypeCounter(0)
    { }

    int getTypeNumber(const eptr& expr);
    std::vector<eqptr> solveSystem();
};


#endif //TASKS_TYPIZATION_H
