#include "answer.hpp"


Answer::Answer(User* own, User* giv, Poll& p, Variant& v):
    voice_owner(own),
    voice_giver(giv),
    poll(&p),
    variant(&v),
    type_(((own==giv)?AnswerType::USER:AnswerType::FOLOWER)){}

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
