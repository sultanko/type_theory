//
// Created by sultan on 24.06.15.
//

#include "Application.h"

std::string Application::toString() const
{
    return "(" + left->toString() + " " + right->toString() + ")";
}

bool Application::isEqual(const eptr &other) const
{
    if (typeid(*other.get()) == typeid(*this))
    {
        const Application * otherA = static_cast<const Application *>(other.get());
        return left->isEqual(otherA->left) && right->isEqual(otherA->right);
    }
    return false;
}
