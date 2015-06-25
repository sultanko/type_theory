#include <iostream>
#include "Parser/Parser.h"

using namespace std;

int main()
{
    freopen("task3.in", "r", stdin);
    freopen("task3.out", "w", stdout);
    string str;
    string cur;
    while (getline(cin, cur))
    {
        str += cur;
    }
    size_t posSkob = str.find('[');
    string strExpr = str.substr(0, posSkob);
    size_t posSkobEnd = str.find(']', posSkob);
    size_t posEq = str.find(":=");
    string strVar = str.substr(posSkob + 1, posEq - posSkob - 1);
    string strSubst = str.substr(posEq + 2, posSkobEnd - 2);
    eptr expr = Parser::parseString(strExpr);
    eptr var = Parser::parseString(strVar);
    eptr subst = Parser::parseString(strSubst);
    set<string> vars = subst->getFreeVariables();
    try
    {
        cout << expr->sustitute(var->toString(), subst, vars).expr->toString() << "\n";
    } catch (const Expression::SubtitutionException& e) {
        cout << e.what() << "\n";
    }

    return 0;
}
