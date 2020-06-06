#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <string>
#include <utility>

#include "user.hpp"
#include "poll.hpp"

enum struct AnswerType
{
    USER=0,
    FOLOWER
};



class Answer
{
private:
    class User* voice_owner;
    class User* voice_giver;
    class Poll* poll;
    class Variant* variant;
    AnswerType type_;

public:
    Answer(User* own, User* giv, Poll& p, Variant v);
    Answer(const Answer& other) = default;
    AnswerType type() const { return type_; }
    class Variant* getVariant() const { return variant; }
    class Poll* getPoll() const { return poll;}
    class User* getVoiceOwner() const {return voice_owner;}
    class User* getVoiceGiver() const {return voice_giver;}
//    bool operator==(const Answer& other){ return type_==other.type_;}
    bool operator<(Answer other){ return true;}

};



#endif // ANSWER_HPP
