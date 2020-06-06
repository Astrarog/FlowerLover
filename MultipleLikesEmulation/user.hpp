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
//    std::string id;
//    User* itself = this;
    std::string name;
    std::set<User*> followers;
    std::set<User*> followed_to;
    std::map<Poll, UserAnswers> answers;
public:
    User();
    void Follow(User* user) { followed_to.insert(user); (*user).followers.insert(this); }
    void Unfollow(User* user) { followed_to.erase(user); (*user).followers.erase(this); }
    void Answer(Poll&, const Variant&);
};

#endif // USER_HPP
