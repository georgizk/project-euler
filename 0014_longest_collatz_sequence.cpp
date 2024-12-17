/*
<p>The following iterative sequence is defined for the set of positive integers:</p>
<ul style="list-style-type:none;">
<li>$n \to n/2$ ($n$ is even)</li>
<li>$n \to 3n + 1$ ($n$ is odd)</li></ul>
<p>Using the rule above and starting with $13$, we generate the following sequence:
$$13 \to 40 \to 20 \to 10 \to 5 \to 16 \to 8 \to 4 \to 2 \to 1.$$</p>
<p>It can be seen that this sequence (starting at $13$ and finishing at $1$) contains $10$ terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at $1$.</p>
<p>Which starting number, under one million, produces the longest chain?</p>
<p class="note"><b>NOTE:</b> Once the chain starts the terms are allowed to go above one million.</p>
*/

#include <iostream>
#include <cstdint>

int main()
{
    uint64_t longestChainSize{0};
    uint64_t longestChainStart{1};

    for (uint64_t start{2}; start < 1'000'000; ++start)
    {
        uint64_t chainSize{1};
        uint64_t seq{start};
        while (seq != 1)
        {
            ++chainSize;
            if (seq & 1)
            {
                seq = seq*3 + 1;
            }
            else
            {
                seq = seq >> 1;
            }
        }
        if (chainSize > longestChainSize)
        {
            longestChainSize = chainSize;
            longestChainStart = start;
        }
    }

    std::cout << longestChainStart << std::endl;
    std::cout << longestChainSize << std::endl;
}