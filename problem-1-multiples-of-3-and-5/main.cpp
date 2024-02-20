#include <iostream>

unsigned int multiples3and5(const unsigned int limit)
{
    unsigned int sum = 0;
    for(unsigned int n = 0; n < limit; ++n)
    {
        if(n % 3 == 0 || n % 5 == 0)
        {
            sum += n;
        }
    }
    return sum;
}

int main()
{
    const unsigned int limit = 1000;
    const unsigned int numMultiples = multiples3and5(limit);
    std::cout << "MultiplesOf3And5(" << limit << ") = " << numMultiples << "\n";
    return 0;
}