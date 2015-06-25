#include <iostream>
#include "Parser/Parser.h"
#include "Normalization/Normalization.h"

using namespace std;

int main()
{
//    freopen("HW4/oneminute.in", "r", stdin);
    freopen("task4.in", "r", stdin);
    freopen("task4.out", "w", stdout);
    string str;
    string cur;
    while (getline(cin, cur))
    {
        str += cur;
    }
    eptr expr = Parser::parseString(str);
    try
    {
        cout << Normalization::normalize(expr)->toString() << "\n";
    } catch (const Expression::SubtitutionException& e) {
        cout << e.what() << "\n";
    }

    return 0;
}
