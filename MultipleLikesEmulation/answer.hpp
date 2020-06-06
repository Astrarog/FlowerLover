#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <string>

#include "user.hpp"
#include "poll.hpp"

enum struct AnswerType
{
    USER,
    FOLOWER
};


class Answer
{
private:
    User* voice_owner;
    User* voice_giver;
    Poll* poll;
    const Variant* variant;
public:
    const AnswerType type;


public:
    Answer(User* own, User* giv, Poll& p, const Variant& v);

};

#endif // ANSWER_HPP
