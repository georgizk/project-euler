/*
<p>If the numbers $1$ to $5$ are written out in words: one, two, three, four, five, then there are $3 + 3 + 5 + 4 + 4 = 19$ letters used in total.</p>
<p>If all the numbers from $1$ to $1000$ (one thousand) inclusive were written out in words, how many letters would be used? </p>
<br><p class="note"><b>NOTE:</b> Do not count spaces or hyphens. For example, $342$ (three hundred and forty-two) contains $23$ letters and $115$ (one hundred and fifteen) contains $20$ letters. The use of "and" when writing out numbers is in compliance with British usage.</p>
*/
#include <iostream>
#include <string>
#include <map>

std::map<uint64_t, std::string> DIGIT_NAMES
{
    { 0, "zero"},
    { 1, "one"},
    { 2, "two"},
    { 3, "three"},
    { 4, "four"},
    { 5, "five"},
    { 6, "six"},
    { 7, "seven"},
    { 8, "eight"},
    { 9, "nine"},
};

std::map<uint64_t, std::string> SPECIAL_NAMES
{
    { 1, "eleven"},
    { 2, "twelve"},
    { 3, "thirteen"},
    { 4, "fourteen"},
    { 5, "fifteen"},
    { 6, "sixteen"},
    { 7, "seventeen"},
    { 8, "eighteen"},
    { 9, "nineteen"},
};

std::map<uint64_t, std::string> TENS_NAMES
{
    { 1, "ten"},
    { 2, "twenty" },
    { 3, "thirty" },
    { 4, "forty" },
    { 5, "fifty" },
    { 6, "sixty" },
    { 7, "seventy" },
    { 8, "eighty" },
    { 9, "ninety" },
};

std::size_t getNameSize(uint64_t number)
{
    if (auto it{DIGIT_NAMES.find(number)}; it != DIGIT_NAMES.end())
    {
        return it->second.size();
    }
    std::size_t result{};
    auto thousands{(number/1000)%10};
    if (thousands)
    {
        std::cout << DIGIT_NAMES.at(thousands) << " thousand";
        result += DIGIT_NAMES.at(thousands).size() + std::string("thousand").size(); 
    }

    auto digit{number%10};
    auto tens{(number/10)%10};
    auto isSpecial = (tens == 1 && digit > 0);
    auto hundreds{(number/100)%10};
    if (hundreds)
    {
        std::cout << DIGIT_NAMES.at(hundreds) << " hundred";
        result += DIGIT_NAMES.at(hundreds).size() + std::string("hundred").size();

        if (digit || tens)
        {
            std::cout << " and ";
            result += std::string("and").size();
        }
    }
    if (isSpecial)
    {
        std::cout << SPECIAL_NAMES.at(digit) << "\n";
        result += SPECIAL_NAMES.at(digit).size();
        return result;
    }

    if (tens)
    {
        std::cout << TENS_NAMES.at(tens);
        result += TENS_NAMES.at(tens).size();
    }

    if (digit || number == 0)
    {
        if (tens)
        {
            std::cout << "-";
        }
        std::cout << DIGIT_NAMES.at(digit);
        result += DIGIT_NAMES.at(digit).size();
    }
    std::cout << "\n";

    return result;
}

int main()
{
    std::size_t totalSize{};
    for (uint64_t i{1}; i <= 1000; ++i)
    {
        totalSize += getNameSize(i);
    }
    std::cout << totalSize << std::endl;
    // std::cout << getNameSize(112) << std::endl;
}