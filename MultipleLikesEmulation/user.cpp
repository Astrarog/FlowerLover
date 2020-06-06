#include "user.hpp"
#include "answer.hpp"

User::User()
{

}

void User::Answer(Poll& poll, const Variant& var)
{
    class Answer my_answer(this, this, poll, var);
    (this->answers)[poll].insert(my_answer);
    for (User* follower : followers)
    {
        class Answer follower_answer(follower, this, poll, var);
        if ((follower->answers).at(poll))
        {
            (follower->answers)[poll].insert(follower_answer);
        }

        // check if we get more ansers for
    }
}
