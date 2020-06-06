#include "user.hpp"
#include "answer.hpp"

User::User()
{

}

void User::Answer(Poll& poll, const Variant& var)
{
    class Answer my_answer(this, this, poll, var);
    (this->answers)[poll].AddAnswer(my_answer);
    poll.Set(*this, my_answer);
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
            std::pair<bool, Variant> oldV = (this->answers)[poll].getUserVoice();
            (follower->answers)[poll].AddAnswer(follower_answer);
            std::pair<bool, Variant> newV = (this->answers)[poll].getUserVoice();
            if(oldV.first == true && oldV.first == false)
            {
                poll.Unset(*follower, follower_answer);
            }
            else if(oldV.first == false && oldV.first == true)
            {
                poll.Set(*follower, follower_answer);
            }
        }
        else
        {
            (follower->answers)[poll].AddAnswer(follower_answer);
            poll.Set(*follower, follower_answer);
        }

        // check if we get more ansers for
    }
}


void UserAnswers::AddAnswer(const Answer& answer)
{
    if(answer.type()==AnswerType::FOLOWER)
    {
        answersFromTrusted.insert(answer);
        voicesFromTrusted[answer.getVariant()] ++;
    }
    else
    {
        answeredItself = true;
        userAnswer = answer;
    }
}

void UserAnswers::RemoveAnswer(const Answer& answer)
{
    if(answer.type()==AnswerType::FOLOWER)
    {
        answersFromTrusted.erase(answer);
        assert(voicesFromTrusted[answer.getVariant()] > 0);
        voicesFromTrusted[answer.getVariant()] --;
    }
    else
    {
        answeredItself = false;
    }
}


std::pair<bool, Variant> UserAnswers::getUserVoice() const
{
    assert(answeredItself||!(answersFromTrusted.empty()));
    if(answeredItself)
    {
        return std::make_pair(true, userAnswer.getVariant());
    }
    else
    {
        size_t maxSize;
        Variant maxVar;
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
