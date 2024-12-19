/*
<p>Starting in the top left corner of a $2 \times 2$ grid, and only being able to move to the right and down, there are exactly $6$ routes to the bottom right corner.</p>
<div class="center">
<img src="resources/images/0015.png?1678992052" class="dark_img" alt=""></div>
<p>How many such routes are there through a $20 \times 20$ grid?</p>
*/

#include <iostream>
#include <tuple>
#include <set>
#include <cstdint>
#include <numeric>
#include <vector>
#include <map>
#include <algorithm>
#include "numbers.h"

using PrimePowers = std::map<uint64_t, int64_t>;
void removeZeroPowers(PrimePowers& n)
{
    for (auto it{n.begin()}; it != n.end();)
    {
        if (it->second == 0)
        {
            it = n.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
PrimePowers multiply(const PrimePowers& a, const PrimePowers& b)
{
    auto result{a};
    for (const auto& [prime, power] : b)
    {
        result[prime] += power;
    }
    removeZeroPowers(result);
    return result;
}
PrimePowers divide(const PrimePowers& a, const PrimePowers& b)
{
    auto result{a};
    for (const auto& [prime, power] : b)
    {
        result[prime] -= power;
    }
    removeZeroPowers(result);
    return result;
}
PrimePowers convertToProductOfPrimes(uint64_t n)
{
    PrimePowers result{};
    if (n < 2)
    {
        // note that 0 can't be represented as product of primes
        // 1 is simply no primes, or all primes with power 0
        return result;
    }

    auto primes = findPrimesInRange(2, n+1);
    if (std::binary_search(primes.begin(), primes.end(), n))
    {
        result[n] = 1;
        return result;
    }
    for (const auto& prime : primes)
    {
        while (true)
        {
            auto [quotient, remainder] = std::div(static_cast<int64_t>(n), static_cast<int64_t>(prime));
            if (remainder == 0)
            {
                n = quotient;
                ++result[prime];
            }
            else
            {
                break;
            }
        }
    }
    return result;
}

int main()
{
    uint64_t size{20};
    // the calculation (size*2)!/(size! * size!) is right, but need to
    // develop a method to calculate such a large factorial
    // there might be a different way to do it without use of factorial

    // the reasoning behind the formula goes like this - for size x size square,
    // you need to go right exactly size times, and down exactly size times
    // there are 2*size total moves you make where you choose between going down or right
    // so you can think of it as a string with r denoting right and d denothing down
    // in a 2x2 case you can have the operations rrdd, rdrd, rddr, drdr, ddrr, drrd
    // for 3x3 it is rrrddd and all its permutations and so on

    // calculating such a large factorial is not possible with uint64_t but it's possible to
    // take advantage of two facts
    // 1. factorial(size*2)/factorial(size) cancels out the 1-20 terms, need just 21-40
    // 2. 21-40 must also be evenly divisible by 20! since it's an integer number of paths
    // 3. therefore, instead of multiplying, represent each number as a multiple of powers 
    //    of prime numbers and only calculate the multiplication result after the division
    PrimePowers result;
    for (uint64_t i{1}; i <= size; ++i)
    {
        result = multiply(result, divide(convertToProductOfPrimes(i + size), convertToProductOfPrimes(i)));
    }

    uint64_t numPaths{1};
    for (const auto& [prime, power] : result)
    {
        for (int64_t p{0}; p < power; ++p)
        {
            numPaths *= prime;
        }
    }
    std::cout << numPaths << std::endl;
}