#ifndef POLL_HPP
#define POLL_HPP
#include <set>
#include <cassert>

#include "user.hpp"

class Poll;

class Variant
{
    const Poll* poll;
    const std::string explanation;
public:
    Variant(const Poll* p, const std::string& expl): poll(p), explanation(expl) {}
//    inline void AddVoices(size_t to_add) { count_voices += to_add; }
//    inline void SubVoices(size_t to_sub) { assert(count_voices>=to_sub); count_voices -= to_sub; }
};


class Poll
{
    std::map<Variant, size_t> choises;
    std::map<User*, Answer*> answers;
    const std::string description;
public:
    Poll();
    void ReseiveAnswers(std::set<Answer*>);

};

#endif // POLL_HPP
