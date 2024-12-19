#pragma once

#include <string_view>
#include <sstream>
#include <set>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <fstream>
#include <stdexcept>

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
    return (a/gcd)*(b/gcd)*gcd;
}

std::vector<uint64_t> KNOWN_PRIMES{2};
inline std::vector<uint64_t> getPrimesInRange(uint64_t start, uint64_t end)
{
    auto first = std::lower_bound(KNOWN_PRIMES.begin(), KNOWN_PRIMES.end(), start);
    auto last = std::upper_bound(first, KNOWN_PRIMES.end(), end);
    return std::vector<uint64_t>(first, last);
}

inline std::vector<uint64_t> generateOdds(uint64_t start, uint64_t end)
{
    std::vector<uint64_t> odds((end - start) >> 1, 0);
    uint64_t i{start >> 1};
    std::generate(odds.begin(), odds.end(), [&i]
    {
        return (i++ * 2) + 1;
    });
    return odds;
}

template <typename Iter>
inline std::forward_list<uint64_t> calculateNonPrime(uint64_t prime, Iter begin, Iter end)
{
    std::forward_list<uint64_t> toErase;
    std::transform(begin, end, std::front_inserter(toErase), [&prime](const auto& multiple)
    {
        return prime * multiple;
    });
    return toErase;
}

inline std::set<uint64_t>::iterator reduce(std::set<uint64_t>::iterator primeIt, std::set<uint64_t>& candidates)
{
    auto limit = std::upper_bound(primeIt, candidates.end(), *candidates.rbegin() / *primeIt);
    auto toErase = calculateNonPrime(*primeIt, primeIt, limit);
    if (toErase.empty())
    {
        return candidates.end();
    }    
    ++primeIt;
    for (const auto& it : toErase)
    {
        candidates.erase(it);
    }
    return primeIt;
}

inline std::vector<uint64_t> findPrimesInRange(uint64_t start, uint64_t end)
{
    auto largestKnownPrime = KNOWN_PRIMES.back();
    if (end < largestKnownPrime)
    {
        return getPrimesInRange(start, end);
    }
    if (start < 2)
    {
        start = 2;
    }
    auto genStart{start};
    if (genStart < largestKnownPrime)
    {
        genStart = largestKnownPrime;
    }

    auto odds = generateOdds(start, end);
    std::set<uint64_t> potentialPrimes{odds.begin(), odds.end()};
    for (auto it{potentialPrimes.begin()}; it != potentialPrimes.end(); it = reduce(it, potentialPrimes));
    auto it = std::lower_bound(potentialPrimes.cbegin(), potentialPrimes.cend(), KNOWN_PRIMES.back()+1);
    if (it != potentialPrimes.cend())
    {
        KNOWN_PRIMES.insert(KNOWN_PRIMES.end(), it, potentialPrimes.cend());
    }
    return getPrimesInRange(start, end);
}

class NaturalNumber
{
public:
NaturalNumber() = default;
NaturalNumber(std::string_view number)
{
    digits.reserve(number.size());
    for (auto it{number.rbegin()}; it != number.rend(); ++it)
    {
        int digit{*it - '0'};
        if (digit > 9 || digit < 0)
        {
            throw std::invalid_argument{std::string(number)};
        } 
        digits.push_back(static_cast<uint8_t>(digit));
    }
}
uint8_t& operator[] (std::size_t idx)
{
    if (idx >= digits.size())
    {
        digits.resize(idx+1, 0);
    }
    return digits[idx];
}

std::vector<uint8_t> digits;
};

std::ostream& operator<<(std::ostream& os, const NaturalNumber& n)
{
    std::string s;
    s.resize(n.digits.size(), '0');
    std::transform(n.digits.rbegin(), n.digits.rend(), s.begin(), [](auto d)
    {
        return d + '0';
    });
    os << s;
    return os;
}

uint8_t getDigit(const NaturalNumber& n, std::size_t idx)
{
    if (idx < n.digits.size())
    {
        return n.digits[idx];
    }
    return 0;
}

NaturalNumber& setDigit(NaturalNumber& n, std::size_t idx, uint8_t digit)
{
    if (idx >= n.digits.size())
    {
        n.digits.resize(idx + 1, 0);
    }
    n.digits[idx] = digit;
    return n;
}

NaturalNumber& append(NaturalNumber& a, const NaturalNumber& b)
{
    a.digits.reserve(b.digits.size());
    for (std::size_t i{0}; i < b.digits.size(); ++i)
    {
        setDigit(a, i, getDigit(a, i) + getDigit(b, i));
        if (auto d{getDigit(a, i)}; d > 9)
        {
            setDigit(a, i, d - 10);
            setDigit(a, i+1, 1 + getDigit(a, i+1));
        }
    }
    for (std::size_t i{b.digits.size()}; i < a.digits.size() + 1; ++i)
    {
        if (auto d{getDigit(a, i)}; d > 9)
        {
            setDigit(a, i, d - 10);
            setDigit(a, i+1, 1 + getDigit(a, i+1));
        }
    }
    return a;
}

NaturalNumber add(const NaturalNumber& a, const NaturalNumber& b)
{
    NaturalNumber result{a};
    return append(result, b);
}

NaturalNumber multiply(const NaturalNumber& a, const NaturalNumber& b)
{
    NaturalNumber result;
    for (uint64_t j{0}; j < b.digits.size(); ++j)
    {
        for (uint64_t i{0}; i < a.digits.size(); ++i)
        {
            auto digitMult{b.digits[j] * a.digits[i]};
            for (uint32_t k{0}; digitMult != 0; ++k)
            {
                auto [quotient, remainder] = std::div(digitMult + getDigit(result, i+j+k), 10);
                digitMult = quotient;
                setDigit(result, i + j + k, remainder);
            }
        }
    }
    return result;
}
