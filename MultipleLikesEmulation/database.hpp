#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <set>

#include "poll.hpp"
#include "user.hpp"

class database
{
    std::set<Poll> polls;
    std::set<User> users;
public:
    database();
};

#endif // DATABASE_HPP
