/*
<p>A Pythagorean triplet is a set of three natural numbers, $a \lt b \lt c$, for which,
$$a^2 + b^2 = c^2.$$</p>
<p>For example, $3^2 + 4^2 = 9 + 16 = 25 = 5^2$.</p>
<p>There exists exactly one Pythagorean triplet for which $a + b + c = 1000$.<br>Find the product $abc$.</p>
*/
#include <iostream>

int main()
{
    // a + b + c = 1000
    // a^2 + b^2 = c^2
    // so c must be greater than a and b, can do a brute force search
    // (1000 - (a + b))^2 = a^2 + b^2
    // 1000^2 - 2 * 1000 * (a + b) + (a+b)^2 = a^2 + b^2
    // 1000^2 - 2 * 1000 * (a + b) + a^2 + 2ab + b^2 = a^2 + b^2
    // 1000^2 + 2*a*b = 2000*a + 2000*b
    // (1000^2 / 2) + a*b = 1000*(a+b)
    uint64_t offset{1000*1000/2};
    for (uint64_t a{1}; a < 500; ++a)
    {
        for (uint64_t b{a}; b < 500; ++b)
        {
            if (((offset + a*b) - (a+b)*1000) == 0)
            {
                std::cout << a << " " << b << std::endl;
                auto c{1000 - a - b};
                std::cout << c << std::endl;
                std::cout << a * a << std::endl;
                std::cout << b * b << std::endl;
                std::cout << c * c << std::endl;
                std::cout << a * b * c << std::endl;
                return 0;
            }
        }
    }
}