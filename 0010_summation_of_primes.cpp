/*
<p>The sum of the primes below $10$ is $2 + 3 + 5 + 7 = 17$.</p>
<p>Find the sum of all the primes below two million.</p>
*/

#include <iostream>
#include <numeric>
#include "numbers.h"

int main()
{
    auto primes = findPrimesInRange(2, 2'000'001);
    std::cout << std::accumulate(primes.begin(), primes.end(), uint64_t{0});
}