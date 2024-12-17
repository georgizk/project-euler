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

inline void findPrimesUpTo(uint64_t upperBound)
{
    auto largestKnownPrime = KNOWN_PRIMES.back();
    if (largestKnownPrime >= upperBound)
    {
        return;
    }

    // we know a-priori that even numbers except 2 are not prime
    // suppose we have a set of 20 odd numbers starting from 3 and want to find which of them are prime
    // 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41
    // the leftmost number is prime, store it as a known prime
    // we multiply it by each number in the set including itself until it exceeds the largest (41)
    // if the multiplication result matches a number in the set,
    // it is not prime and should not be used as a multiple in the next iteration
    // 3*3 -> 9
    // 3*5 -> 15
    // 3*7 -> 21
    // 3*9 -> 27
    // 3*11 -> 33
    // 3*13 -> 39
    // remove them from the set, new set is
    // 3 5 7 11 13 17 19 23 25 29 31 35 37 41
    // 5*5 -> 25
    // 5*7 -> 35
    // remove...
    // 3 5 7 11 13 17 19 23 29 31 37 41
    // 7*7 > 41, so all remaining numbers are prime
    // instead of storing the number, use the index (first element is 1) in the vector
    // to represent number n = 1 + 2*i
    // backwards mapping, (n - 1)/2 = i

    std::vector<bool> candidatesBase(upperBound, false);
    // std::vector<uint64_t> potentialPrimes;
    uint64_t startingIndex{0};
    // 0 -> 3
    // 1 -> 5
    // 2 -> 7
    // 3 -> 9
    while(true)
    {   
        uint64_t n{startingIndex*2 + 3};
        // if (n == 37)
        // std::cout << "n " << n << std::endl;
        if (n*n >= upperBound * 2 + 3)
        {
            break;
        }
        std::list<uint64_t> indices;
        // std::cout << "n:" << n << std::endl;
        // std::cout << "startingIndex " << startingIndex << std::endl;
        for (uint64_t i{startingIndex}; i < upperBound; ++i)
        {
            auto m{2*i + 3};
            if (candidatesBase[i])
            {
                // if (n == 37)
                // std::cout << "m " << m << " excluded\n";
                continue;
            }
            // if (n == 37)
            // std::cout << "m " << m << std::endl;
            auto nonPrimeMultiple = n * m;
            // std::cout << "np " << nonPrimeMultiple << std::endl;
            auto nonPrimeIdx = (nonPrimeMultiple - 3)>>1;
            if (nonPrimeIdx >= upperBound)
            {
                break;
            }
            indices.push_back(nonPrimeIdx);
            //std::cout << "nonPrimeMultiple " << nonPrimeMultiple << std::endl;
            // if (newN >= upperBound)
            // {
            //     break;
            // }
            // candidates[newI - 1] = true;
        }
        for (const auto& idx : indices)
        {
            candidatesBase[idx] = true;
        }
        while(++startingIndex < upperBound && candidatesBase[startingIndex])
        {
            // uint64_t n{startingIndex*2 + 3};
            // if (!candidates[startingIndex])
            // {
            //     std::cout << n << " is prime\n";
            //     break;
            // }
            // else
            // {
            //     std::cout << n << " is not prime\n";
            // }
        }
    }
    // std::cout << candidates.size() << std::endl;
    // for (std::size_t i{1}; i <= candidates.size(); ++i)
    // {
    //     std::cout << largestKnownPrime + i * 2 << std::endl;
    // }
    // candidates.resize((upperBound - largestKnownPrime) / 2);
    // std::generate(candidates.begin(), candidates.end(), [&largestKnownPrime]
    // {
    //     return (largestKnownPrime += 2);
    // });

    std::vector<uint64_t> primes;
    for (uint64_t i{0}; i < candidatesBase.size(); ++i)
    {
        if (candidatesBase[i])
        {
            continue;
        }
        primes.push_back(2*i + 3);
        // std::cout << 2*i + 3 << std::endl;
    }
    std::cout << primes.size() << std::endl;
    std::cout << primes.at(0) << std::endl;
    std::cout << primes.at(1) << std::endl;
    std::cout << primes.at(4) << std::endl;
    std::cout << primes.at(5) << std::endl;
    std::cout << primes.at(6) << std::endl;
    std::cout << primes.at(9999) << std::endl;
    std::cout << primes.at(10000) << std::endl;
    std::cout << primes.at(10001) << std::endl;
    // for (const auto& c : candidates)
    // {
    //     std::cout << c << std::endl;
    // }
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
