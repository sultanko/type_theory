//
// Created by sultan on 24.06.15.
//

#include <iostream>
#include "Parser/Parser.h"
#include "Typization/Typization.h"


using namespace std;

int main()
{
    freopen("task6.in", "r", stdin);
    freopen("task6.out", "w", stdout);
    string str;
    string cur;
    while (getline(cin, cur))
    {
        str.append(cur);
    }
    eptr expr = Parser::parseString(str);
    Typization typizator;
    try
    {
        int exprNum = typizator.getTypeNumber(expr);
        vector<eqptr> solution = typizator.solveSystem();
        unordered_map<string, string> typeMap;
        string exprName = "a" + to_string(exprNum);
        for (const eqptr& item : solution)
        {
            typeMap.insert(make_pair(item->getLeft()->toString(), item->getRight()->toTypeString()));
        }
        if (typeMap.find(exprName) == typeMap.end())
        {
            cout << exprName << "\n";
        }
        else
        {
            cout << typeMap[exprName] << "\n";
        }
        for (const std::string& item : expr->getFreeVariables())
        {
            cout << item << ":" << typeMap[item] << "\n";
        }
    } catch (const UnificationException& e) {
        cout << "Выражение не имеет типа" <<"\n";
    }

    return 0;
}

