#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <string>
#include <utility>

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
    Variant* variant;
    AnswerType type_;

public:
    Answer(User* own, User* giv, Poll& p, Variant& v);
    Answer(const Answer& other) = default;
    AnswerType type() const { return type_; }
    Variant getVariant() const { return *variant; }

};


class UserAnswers
{
    std::set<Answer> answersFromTrusted;
    std::map<Variant, size_t> voicesFromTrusted;
    bool answeredItself = false;
    Answer userAnswer;
public:
    void AddAnswer(const Answer&);
    void RemoveAnswer(const Answer&);
    std::pair<bool, Variant> getUserVoice() const;
};

#endif // ANSWER_HPP
