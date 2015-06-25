//
// Created by sultan on 24.06.15.
//

#ifndef TASK1_EXPRESSION_H
#define TASK1_EXPRESSION_H

#include <string>
#include <set>
#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>

class Expression;

typedef std::shared_ptr<const Expression> eptr;

struct FreeVars
{
    std::set<std::string> freeVars;
    bool wasComputed;

    void setComputed(const std::set<std::string>& vars)
    {
        freeVars = vars;
        wasComputed = true;
    }

    const std::set<std::string> &getFreeVars() const
    {
        return freeVars;
    }
};

struct ExpressionHashState
{
    size_t hash;
    bool computed;
    void setComputed(size_t hash)
    {
        this->hash = hash;
        computed = true;
    }

    size_t getHash() const
    {
        return hash;
    }

};

class Expression
{
private:
    std::shared_ptr<ExpressionHashState> hash;
protected:
    std::shared_ptr<FreeVars> freeVars;
    std::string strExpr;
    Expression() : hash(new ExpressionHashState()), freeVars(new FreeVars()) {}
public:
    struct SubstitutionState
    {
        eptr expr;
        bool used;
        template <typename T>
        SubstitutionState(T expr, bool used) : expr(expr), used(used) {}
    };
    struct SubtitutionException : public std::exception
    {
        std::string varName;
        SubtitutionException(const std::string& var)
                : varName("Нет свободы для подстановки " + var) {}
        const char *what() const _GLIBCXX_USE_NOEXCEPT override;
    };
    virtual const std::string & toString() const = 0;
    virtual bool isEqual(const eptr& other) const = 0;
    virtual const std::set<std::string> & getFreeVariables() const = 0;
    virtual SubstitutionState sustitute(
            const std::string& variable,
            const eptr& expr,
            const std::set<std::string>& freeVars) const = 0;
    virtual eptr normalizeSubstitute(
            const std::string &var,
            const eptr &subst
    ) const = 0;
    size_t getHash() const;
    virtual ~Expression() {};

};

struct Expression_hash_fn
{
    size_t operator()(const eptr& expr) const
    {
        return expr->getHash();
    }
};

struct Expression_equals_fn
{
    bool operator()(const eptr& e1, const eptr& e2) const
    {
        return e1->isEqual(e2);
    }
};




#endif //TASK1_EXPRESSION_H
