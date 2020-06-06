#ifndef POLL_HPP
#define POLL_HPP
#include <set>
#include <cassert>

#include "user.hpp"

class Variant
{
    std::string explanation;
public:
    Variant(const std::string& expl): explanation(expl) {}
    Variant(){}
    bool operator== (const Variant& other) const { return this->explanation==other.explanation; }
    bool operator<(const Variant& other) const { return this->explanation==other.explanation; }
};


class Poll
{
    std::map<class Variant*, size_t> choises;
    std::map<class User*, class Answer*> answers;
    const std::string description;
public:
    Poll(const std::string& desc, std::set<class Variant>& vars);
    void Set(class User *, class Answer *);
    void Unset(class User *, class Answer *);
    bool operator== (const Poll& other) const { return this->description==other.description; }
    bool operator< (const Poll& other) const { return this->description<other.description; }
};

#endif // POLL_HPP
