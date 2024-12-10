#pragma once

#include <string_view>
#include <sstream>

inline bool isPalindrome(std::string_view str)
{
    auto itLeft = str.cbegin();
    auto itRight = str.crbegin();
    auto itEnd = itLeft + str.size() / 2;

    while (itLeft != itEnd)
    {
        if (*itLeft != *itRight)
        {
            return false;
        }
        ++itLeft;
        ++itRight;
    }
    return true;
}

template <typename T>
inline std::string toString(T&& val)
{
    std::stringstream str;
    str << val;
    return str.str();
}
