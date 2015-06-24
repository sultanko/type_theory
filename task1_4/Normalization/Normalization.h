//
// Created by sultan on 24.06.15.
//

#ifndef TASK4_NORMALIZATION_H
#define TASK4_NORMALIZATION_H

#include "../Parser/Expression.h"
#include <unordered_map>

class Normalization
{
private:
    static std::unordered_map<eptr, eptr, Expression_hash_fn, Expression_equals_fn> headMem;
    static std::unordered_map<eptr, eptr, Expression_hash_fn, Expression_equals_fn> mem;

public:
    static void clear() { headMem.clear(); mem.clear(); }
    static eptr normalize(const eptr& expr);
    static eptr headNormalize(const eptr& expr);
};


#endif //TASK4_NORMALIZATION_H
