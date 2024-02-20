#include <cmath>
#include <iostream>

unsigned int calculateFibonacciNumber(const unsigned int n)
{
    const auto sqrt5 = std::sqrt(5);
    return static_cast<unsigned int>(1 / sqrt5 * (std::pow((1 + sqrt5) / 2, n) - std::pow((1 - sqrt5) / 2, n)));
}

unsigned int evenFibonacciNumbers(const unsigned int limit)
{
    unsigned int sum = 0;
    unsigned int n = 1;
    unsigned int fib = 0;
    do
    {
        fib = calculateFibonacciNumber(n);
        if (fib % 2 == 0)
        {
            sum += fib;
        }
        n += 1;
    }
    while(fib < limit);
    return sum;
}

int main()
{
    const unsigned int limit = 4000000;
    const unsigned int sum = evenFibonacciNumbers(limit);
    std::cout << "EvenFibonacciNumbers(" << limit << ") = " << sum << "\n";
    return 0;
}