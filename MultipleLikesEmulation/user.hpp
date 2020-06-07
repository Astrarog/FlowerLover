#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

#include "answer.hpp"
#include "poll.hpp"

class UserAnswers;

class User
{
    std::string name;
    std::set<class User*> followers;
    std::set<class User*> followed_to;
    std::map<Poll, UserAnswers> answers;
public:
    User(const std::string& n);
    void Follow(class User* user) { followed_to.insert(user); (*user).followers.insert(this); }
    void Unfollow(class User* user);
    void Answer(class Poll&, Variant&);
    bool operator==(const User& other){ return name==other.name;}
    bool operator<(const User& other){ return name<other.name;}
};

class UserAnswers
{
    std::set<class Answer *> answersFromTrusted;
    std::map<class Variant*, size_t> voicesFromTrusted;
    bool answeredItself = false;
    class Answer* userAnswer;
public:
    void AddAnswer(Answer&);
    void RemoveAnswer(Answer&);
    std::pair<bool, Variant*> getUserVoice() const;
    bool isAnsweredItself() const { return answeredItself; }
    friend void User::Unfollow(User*);
    bool operator< (const UserAnswers& other){ return answeredItself<other.answeredItself;}
};


#endif // USER_HPP
