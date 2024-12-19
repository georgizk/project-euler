/*
<p>$2^{15} = 32768$ and the sum of its digits is $3 + 2 + 7 + 6 + 8 = 26$.</p>
<p>What is the sum of the digits of the number $2^{1000}$?</p>
*/

#include "numbers.h"
#include <iostream>
#include <numeric>

int main()
{
    // it's rather obvious that 2^1000 will not fit inside 64 bits,
    // so need to use our large number class
    // adding a multiply method should do the trick
    NaturalNumber result{"1"};
    NaturalNumber two{"2"};
    for (uint32_t i{0}; i < 1000; ++i)
    {
        result = multiply(result, two);
    }

    std::cout << "result: " << result << std::endl;
    std::cout << "sumOfDigits: " << std::accumulate(result.digits.begin(), result.digits.end(), uint64_t{0}) << std::endl;
}