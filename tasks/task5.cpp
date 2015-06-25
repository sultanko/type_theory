//
// Created by sultan on 24.06.15.
//

#include <iostream>
#include "TermParser/TermParser.h"
#include "Unification/Unification.h"


using namespace std;

int main()
{
    freopen("task5.in", "r", stdin);
    freopen("task5.out", "w", stdout);
    string str;
    Unification unificator;
    while (getline(cin, str))
    {
        size_t posEq = str.find('=');
        tptr termLeft = TermParser::parseString(str.substr(0, posEq));
        tptr termRight = TermParser::parseString(str.substr(posEq + 1));
        unificator.addEquation(new Equation(termLeft, termRight));
    }
    try
    {
        vector<eqptr> solve = unificator.solveSystem();
        for (auto item : solve)
        {
            cout << item->toString() << "\n";
        }
    } catch (const UnificationException& e) {
        cout << e.what() << "\n";
    }

    return 0;
}

