//
// Created by sultan on 26.06.15.
//

#include "Typization.h"
#include "../Parser/Variable.h"
#include "../Parser/Application.h"
#include "../TermParser/TermVariable.h"
#include "../TermParser/Function.h"
#include "../Parser/Abstraction.h"

using std::vector;
using std::string;
using std::unordered_map;

int Typization::getTypeNumber(const eptr &expr)
{
    if (typeid(*expr.get()) == typeid(Variable))
    {
        const std::string varName = expr->toString();
        if (contains(absVars, varName))
        {
            return absVars[varName];
        }
        if (contains(context, varName))
        {
            return context[varName];
        }
        tptr typeVar = createNewVar();
        context[varName] = variableTypeCounter;
        unificator.addEquation(
                new Equation(tptr(new TermVariable(varName)), typeVar));
        return variableTypeCounter;
    }
    else if (typeid(*expr.get()) == typeid(Application))
    {
        const Application* application = (const Application*)(expr.get());
        int leftNum = getTypeNumber(application->getLeft());
        int rightNum = getTypeNumber(application->getRight());
        unificator.addEquation(
                new Equation(createNewVar(leftNum),
                             createTypeArrow(rightNum, ++variableTypeCounter)));
        return variableTypeCounter;
    }
    else
    {
        const Abstraction* abstraction = (const Abstraction*) expr.get();
        const std::string& varName = abstraction->getVariable()->toString();
        int previousNum = -1;
        if (contains(absVars, varName))
        {
            previousNum = absVars[varName];
        }
        int varNum = ++variableTypeCounter;
        absVars[varName] = varNum;
        int phraseNum = getTypeNumber(abstraction->getExpr());
        unificator.addEquation(new Equation(createNewVar(), createTypeArrow(varNum, phraseNum)));
        if (previousNum != -1)
        {
            absVars[varName] = previousNum;
        }
        else
        {
            absVars.erase(varName);
        }
        return variableTypeCounter;
    }
}

bool Typization::contains(const std::unordered_map<std::string, int> &container, const std::string &item)
{
    return container.find(item) != container.end();
}

tptr Typization::createNewVar()
{
    return createNewVar(++variableTypeCounter);
}

tptr Typization::createNewVar(int i)
{
    return tptr(new TermVariable("a" + std::to_string(i)));
}

tptr Typization::createTypeArrow(const tptr &l, const tptr &tptr1)
{
    vector<tptr> arg;
    arg.push_back(l);
    arg.push_back(tptr1);
    return tptr(new Function("f", arg));
}

tptr Typization::createTypeArrow(int l, int r)
{
    return createTypeArrow(createNewVar(l), createNewVar(r));
}

std::vector<eqptr> Typization::solveSystem()
{
    using std::cout;
//    cout << "Context\n";
//    for (auto item : context)
//    {
//        cout << item.first << " = " << item.second << "\n";
//    }
//    cout << "\n";
    return unificator.solveSystem();
}
