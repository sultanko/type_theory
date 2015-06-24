#include <iostream>
#include "Parser/Parser.h"

using namespace std;

int main()
{
    freopen("task2.in", "r", stdin);
    freopen("task2.out", "w", stdout);
    string str;
    string cur;
    while (getline(cin, cur))
    {
        str += cur;
    }
    eptr expr = Parser::parseString(str);
    set<string> vars = expr->getFreeVariables();
    for (string var : vars)
    {
        cout << var << "\n";
    }
    return 0;
}