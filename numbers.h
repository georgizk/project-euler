#pragma once

#include <string_view>
#include <sstream>
#include <set>
#include <cstdint>
#include <iostream>

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
std::string toString(T&& val)
{
    std::stringstream str;
    str << val;
    return str.str();
}

// get greatest common denominator using euclidian algorithm
inline uint64_t getGcdEuclidian(uint64_t a, uint64_t b)
{
    if (b == 0)
    {
        return a;
    }
    return getGcdEuclidian(b, a % b);
}

// get least common multiple using gcd euclidian algorithm
inline uint64_t getLcmEuclidian(uint64_t a, uint64_t b)
{
    auto gcd = getGcdEuclidian(a, b);
    // std::cout << "gcd a:" << a << " b:" << b << " = " << gcd << std::endl;
    // std::cout << "a*b=" << a*b << std::endl;
    // std::cout << "a/gcd=" << a/gcd << std::endl;
    // std::cout << "b/gcd=" << b/gcd << std::endl;
    // std::cout << "(a*b)/gcd = " << (a*b)/gcd << std::endl;
    return (a/gcd)*(b/gcd)*gcd;
}

// std::set<uint64_t> KNOWN_PRIMES{2};

// inline bool isPrime(uint64_t val)
// {
//     auto largestPrime = *KNOWN_PRIMES.crbegin();
//     if (val <= largestPrime)
//     {
//         return KNOWN_PRIMES.count(val);
//     }
//     auto halfVal = val / 2;
    
// }
