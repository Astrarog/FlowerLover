#include "answer.hpp"


Answer::Answer(User* own, User* giv, Poll& p, const Variant& v):
    voice_owner(own),
    voice_giver(giv),
    poll(&p),
    variant(&v),
    type(((own==giv)?AnswerType::USER:AnswerType::FOLOWER)){}
