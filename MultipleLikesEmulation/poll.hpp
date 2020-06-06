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
    std::map<Variant, size_t> choises;
    std::map<User*, Answer*> answers;
    const std::string description;
public:
    Poll(const std::string& desc, const std::set<Variant>& vars);
    void Set(User&, Answer&);
    void Unset(User&, Answer&);

};

#endif // POLL_HPP
