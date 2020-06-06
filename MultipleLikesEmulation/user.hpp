#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

#include "answer.hpp"
#include "poll.hpp"
class User;

class User
{
    std::string id;
    std::string name;
    std::vector<User*> followers;
    std::vector<User*> followed_to;
    std::map<Poll, std::set<Answer>> a;
public:
    User();
};

#endif // USER_HPP
