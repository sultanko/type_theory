//
// Created by sultan on 24.06.15.
//

#include "Expression.h"

const char *Expression::SubtitutionException::what() const _GLIBCXX_USE_NOEXCEPT
{
    return varName.c_str();
}

size_t Expression::getHash() const
{
    return hash;
}

void Expression::initializeHash()
{
    hash = std::hash<std::string>()(toString());
}
