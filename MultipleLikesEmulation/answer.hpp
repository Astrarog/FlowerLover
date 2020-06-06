#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <string>

#include "user.hpp"

enum struct AnswerType
{
    USER,
    FOLOWER
};


class Answer
{
    AnswerType type;
    User* voice_owner;
    User* voice_giver;
    std::string expalantion;
public:
    Answer();
};

#endif // ANSWER_HPP
