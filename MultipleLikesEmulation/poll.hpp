#ifndef POLL_HPP
#define POLL_HPP
#include "set"

class Variant
{
public:
    Variant();
};


class Poll
{
    std::set<Variant> choises;
public:
    Poll();
};

#endif // POLL_HPP
