#include <string>

#include "user.hpp"
#include "answer.hpp"

User::User(const std::string& n): name(n) {}

void User::Unfollow(User* user)
{
    for(auto& pansw: answers)
    {
        auto poll = pansw.first;
        auto answs = pansw.second;
        for(class Answer* anw : answs.answersFromTrusted)
        {
            if(*(anw->getVoiceGiver()) == *user)
            {
                std::pair<bool, Variant*> oldV = answs.getUserVoice();
                answs.RemoveAnswer(*anw);
                std::pair<bool, Variant*> newV = answs.getUserVoice();
                if(answs.isAnsweredItself())
                {
                    continue;
                }
                if(!(oldV.second == newV.second)&&newV.first == true)
                {
                    poll.Unset(this, anw);

                    User* newGiver;
                    for (const auto& a:answs.answersFromTrusted)
                    {
                        if(*(a->getVariant())==*(newV.second))
                        {
                            newGiver = a->getVoiceGiver();
                        }
                    }
                    class Answer newAnswer(this, newGiver, poll, *(newV.second));
                    poll.Set(this, &newAnswer);
                }
                if(newV.first == false)
                {
                    poll.Unset(this, anw);
                }
            }
        }
    }
    followed_to.erase(user); (*user).followers.erase(this);
}

void User::Answer(Poll& poll, Variant& var)
{
    class Answer my_answer(this, this, poll, var);
    (this->answers)[poll].AddAnswer(my_answer);
    poll.Set(this, &my_answer);
    for (User* follower : followers)
    {
        class Answer follower_answer(follower, this, poll, var);
        if ((follower->answers).count(poll))
        {
            if((follower->answers)[poll].isAnsweredItself())
            {
                (follower->answers)[poll].AddAnswer(follower_answer);
                continue;
            }
            std::pair<bool, Variant*> oldV = (this->answers)[poll].getUserVoice();
            (follower->answers)[poll].AddAnswer(follower_answer);
            std::pair<bool, Variant*> newV = (this->answers)[poll].getUserVoice();
            if(oldV.first == true && newV.first == false)
            {
                poll.Unset(follower, &follower_answer);
            }
            else if(oldV.first == false && newV.first == true)
            {
                poll.Set(follower, &follower_answer);
            }
        }
        else
        {
            (follower->answers)[poll].AddAnswer(follower_answer);
            poll.Set(follower, &follower_answer);
        }
    }
}


void UserAnswers::AddAnswer(Answer& answer)
{
    if(answer.type()==AnswerType::FOLOWER)
    {
        answersFromTrusted.insert(&answer);
        voicesFromTrusted[answer.getVariant()] ++;
    }
    else
    {
        answeredItself = true;
        *userAnswer = answer;
    }
}

void UserAnswers::RemoveAnswer(Answer& answer)
{
    if(answer.type()==AnswerType::FOLOWER)
    {
        answersFromTrusted.erase(&answer);
        assert(voicesFromTrusted[answer.getVariant()] > 0);
        voicesFromTrusted[answer.getVariant()] --;
    }
    else
    {
        answeredItself = false;
    }
}


std::pair<bool, Variant*> UserAnswers::getUserVoice() const
{
    assert(answeredItself||!(answersFromTrusted.empty()));
    if(answeredItself)
    {
        return std::make_pair(true, (userAnswer->getVariant()));
    }
    else
    {
        size_t maxSize;
        Variant* maxVar;
        bool isFirst = true;
        bool canChoose = false;
        for (const auto& var: voicesFromTrusted)
        {
            if(isFirst)
            {
                maxVar = var.first;
                maxSize = var.second;
                isFirst = false;
                continue;
            }
            if(maxSize == var.second)
            {
                canChoose = false;
            }
            else if (maxSize < var.second)
            {
                maxVar = var.first;
                maxSize = var.second;
                canChoose = true;
            }
        }

        return std::make_pair(canChoose, maxVar);
    }
}
