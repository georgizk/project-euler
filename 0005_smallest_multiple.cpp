/*
<p>$2520$ is the smallest number that can be divided by each of the numbers from $1$ to $10$ without any remainder.</p>
<p>What is the smallest positive number that is <strong class="tooltip">evenly divisible<span class="tooltiptext">divisible with no remainder</span></strong> by all of the numbers from $1$ to $20$?</p>
*/

#include <iostream>
#include <vector>
#include <cstdint>
#include <set>
#include "numbers.h"

int main()
{
    // 2520 is smallest number divisible by each of 1-10
    // no need to go through 1-10 again, start from 11-20
    uint64_t smallest{2520};
    for (uint32_t n{11}; n <= 20; ++n)
    {
        smallest = getLcmEuclidian(smallest, n);
    }
    std::cout << smallest << std::endl;
}