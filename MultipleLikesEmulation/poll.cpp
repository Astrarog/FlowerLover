#include "poll.hpp"

Poll::Poll(const std::string& desc, std::set<class Variant>& vars): description(desc)
{
    for(auto var: vars)
    {
        choises[(&var)]=0;
    }
}

void Poll::Set(User* user, Answer* answ)
{
    answers[user]=answ;
    choises[answ->getVariant()] ++;
}


void Poll::Unset(User* user, Answer* answ)
{

    assert(answers.count(user));
    answers.erase(user);
    choises[answ->getVariant()] --;
}
