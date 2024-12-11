/*
<p>The sum of the squares of the first ten natural numbers is,</p>
$$1^2 + 2^2 + ... + 10^2 = 385.$$
<p>The square of the sum of the first ten natural numbers is,</p>
$$(1 + 2 + ... + 10)^2 = 55^2 = 3025.$$
<p>Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is $3025 - 385 = 2640$.</p>
<p>Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.</p>
*/
#include <cstdint>
#include <iostream>

int main()
{
    uint64_t sumOfNumbers{};
    uint64_t sumOfSquares{};

    for (uint64_t n{1}; n <= 100; ++n)
    {
        sumOfNumbers += n;
        sumOfSquares += n*n;
    }
    std::cout << sumOfNumbers * sumOfNumbers - sumOfSquares << std::endl;
}