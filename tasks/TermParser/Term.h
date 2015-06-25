//
// Created by sultan on 25.06.15.
//

#ifndef TASKS_TERM_H
#define TASKS_TERM_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class Term;

typedef std::shared_ptr<const Term> tptr;

class Term
{
public:
    virtual bool isEqual(const tptr& other) const = 0;
    virtual const std::string & toString() const = 0;
    virtual std::string toTypeString() const = 0;
    virtual tptr substitute(const std::string& oldVar, const tptr& replacement) const = 0;
    virtual const std::set<std::string>& getVariables() const = 0;
};


#endif //TASKS_TERM_H
