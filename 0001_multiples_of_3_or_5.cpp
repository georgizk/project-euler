/* 
<p>If we list all the natural numbers below $10$ that are multiples of $3$ or $5$, 
   we get $3, 5, 6$ and $9$. The sum of these multiples is $23$.</p>
<p>Find the sum of all the multiples of $3$ or $5$ below $1000$.</p>
*/

#include <iostream>

int main()
{
   unsigned sum{};
   for (unsigned n{1}; n < 1000; ++n)
   {
      if ((n % 3) == 0 || (n % 5) == 0)
      {
         sum += n;
      }
   }
   std::cout << sum << std::endl;
}