#include "poll.hpp"

Poll::Poll(const std::string& desc, const std::set<Variant>& vars): description(desc)
{
    for(const auto& var: vars)
    {
        choises[var]=0;
    }
}
