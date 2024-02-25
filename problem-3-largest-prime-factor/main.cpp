#include <cmath>
#include <iostream>

using ullong = unsigned long long;

ullong largestPrimeFactor(const ullong num)
{
    ullong largest = 3;
    ullong numMut = num;
    for(ullong n = 3; n * n <= num; n += 2)
    {
        if(numMut % n == 0)
        {
            while(numMut % n == 0)
            {
                numMut /= n;
            }
            if(n > largest)
            {
                largest = n;
            }
        }
    }
    return largest;
}

int main()
{
    const ullong num = 600851475143ULL;
    const ullong factor = largestPrimeFactor(num);
    std::cout << "LargestPrimeFactor(" << num << ") = " << factor << "\n";
    return 0;
}