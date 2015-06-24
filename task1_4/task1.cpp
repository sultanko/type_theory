#include <iostream>
#include "Parser/Parser.h"

using namespace std;

int main()
{
    freopen("task1.in", "r", stdin);
    freopen("task1.out", "w", stdout);
    string str;
    string cur;
    while (getline(cin, cur))
    {
        str += cur;
    }
    eptr expr = Parser::parseString(str);
    cout << expr->toString();
    return 0;
}