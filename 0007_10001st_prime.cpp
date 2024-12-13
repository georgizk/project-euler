/*
<p>By listing the first six prime numbers: $2, 3, 5, 7, 11$, and $13$, we can see that the $6$th prime is $13$.</p>
<p>What is the $10\,001$st prime number?</p>
*/

#include "numbers.h"
#include <iostream>

int main()
{
    auto endPoint = 100000;
    std::vector<uint64_t> primes;
    do
    {
        primes = findPrimesInRange(0, endPoint);
        endPoint += 100000;
    } while (primes.size() < 10001);
    std::cout << primes.at(10000) << std::endl;
}