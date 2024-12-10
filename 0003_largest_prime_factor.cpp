/*
<p>The prime factors of $13195$ are $5, 7, 13$ and $29$.</p>
<p>What is the largest prime factor of the number $600851475143$?</p>
*/
#include <iostream>
#include <cmath>

int main()
{
    long long signed number{600851475143};

    long long signed divisor{3};
    while (divisor < number)
    {
        auto [quotient, remainder] = std::div(number, divisor);
        if (remainder == 0)
        {
            std::cout << divisor << std::endl;
            number = quotient;
            continue;
        }
        else
        {
            divisor += 2;
        }
    }

    std::cout << number << std::endl;
    std::cout << divisor << std::endl;

}