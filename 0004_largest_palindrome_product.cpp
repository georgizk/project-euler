/*
<p>A palindromic number reads the same both ways. 
The largest palindrome made from the product of two $2$-digit numbers is $9009 = 91 \times 99$.</p>
<p>Find the largest palindrome made from the product of two $3$-digit numbers.</p>
*/

#include "numbers.h"
#include <iostream>

int main()
{
    int largestPalindrome{};
    // go from largest to smallest triple digit number (999 to 100)
    for (int i{999}; i > 99; --i)
    {
        // check if a larger palindrome than i squared has already been found
        if (i * i < largestPalindrome)
        {
            break;
        }
        // multiple i by all triple digit numbers less than or equal than i
        // there's no need to check with j larger than i since it will already have
        // been checked with the larger value of i (that is, since i * j = j * i)
        for (int j{i}; j > 99; --j)
        {
            auto product = i * j;
            // if the found product is larger than the largest palindrome seen so far,
            // save it stop checking for smaller j (i * j is necessarily greater than i * (j - 1))
            if (product > largestPalindrome && isPalindrome(toString(product)))
            {
                largestPalindrome = product;
                break;
            }
            // no need to check smaller j if the product is smaller than largest palindrome
            else if (product < largestPalindrome)
            {
                break;
            }
        }
    }

    std::cout << largestPalindrome << std::endl;
}