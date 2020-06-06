#include "answer.hpp"


Answer::Answer(User* own, User* giv, Poll& p, Variant v):
    voice_owner(own),
    voice_giver(giv),
    poll(&p),
    variant(&v),
    type_(((own==giv)?AnswerType::USER:AnswerType::FOLOWER)){}




bool operator<(const Answer& lhs, const Answer& rhs)
{ return int(lhs.type())<int(rhs.type());}
