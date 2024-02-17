/*
    1. Find all prime numbers up to N, using sieve of Eratosthenes. Denote the number of
    prime numbers up to N as P.
    2. Store prime numbers in map, where keys are the LSBs (0, 1, 01, 11, 101, 111, etc.),
    and the values are pairs consisting of the number of numbers having the LSBs and the
    number of numbers that "vote" for 1 on next guess, denoted (M_<lsb>, V_<lsb>).
    3. Calculate the expected number of points by iterating through the map:
    E(N) = sum (M/P * max(V, M-V)/M).
*/

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <utility>

std::vector<bool> sieveOfEratosthenes(const size_t N)
{
    std::vector<bool> prime(N + 1, true);
    prime[0] = prime[1] = false;
    // even numbers are not prime (except 2)
    for(size_t i = 2 * 2; i <= N; i += 2)
    {
        prime[i] = false;
    }
    for(size_t i = 3; i * i <= N; i += 2)
    {
        if(prime[i])
        {
            for(size_t j = i * i; j <= N; j += i)
            {
                prime[j] = false;
            }
        }
    }

    return prime;
}

using BestGuessMap = std::map<std::pair<uint32_t, uint8_t>, std::pair<size_t, size_t>>; //map (lsbs, pos) to (no_nums, votes_one)

double primeGuessing(const uint32_t N)
{
    double expectedPoints = 0.0;
    const auto primes = sieveOfEratosthenes(N);
    const auto numPrimes = std::count_if(primes.begin(), primes.end(), [](bool e){return e;});
    // first guess is always 1, just calculate how many nums end in 1
    {
        uint32_t points = 0;
        for(uint32_t i = 3; i <= N; i += 2)
        {
            if(primes[i])
            {
                points += (i & 1);
            }
        }
        expectedPoints += static_cast<double>(points) / numPrimes;
    }
    // for other guesses, store the best next guess based on previous bits
    const uint32_t maxNumBits = std::ceil(std::log2(N));
    BestGuessMap cache;
    // handle 2 separately
    {
        const auto cacheKey = std::pair{0, 1};
        cache[cacheKey] = std::pair{1, 1};
    }
    for(uint8_t bitPos = 1; bitPos < maxNumBits - 1; ++bitPos)
    {
        const uint32_t bitMask = (1 << bitPos) - 1;
        for(uint32_t i = 3; i <= N; i += 2)
        {
            if(primes[i] && i >= (1 << bitPos))
            {
                const uint32_t lsbs = i & bitMask;
                bool voteOne = i & (1 << bitPos);
                const auto cacheKey = std::pair{lsbs, bitPos};
                if(cache.count(cacheKey))
                {
                    cache[cacheKey].first += 1;
                    cache[cacheKey].second += voteOne;
                }
                else
                {
                    cache[cacheKey] = std::pair{1, voteOne};
                }
            }
        }
    }
    // last guess must be 1, count all numbers >= 2**(maxNumBits - 1)
    {
        uint32_t points = 0;
        for(uint32_t i = static_cast<uint32_t>(std::pow(2, maxNumBits - 1)) + 1; i <= N; i += 2)
        {
            if(primes[i])
            {
                points += 1;
            }
        }
        expectedPoints += static_cast<double>(points) / numPrimes;
    }
    for(const auto& [key, val]: cache)
    {
        expectedPoints += static_cast<double>(val.first) / numPrimes * std::max(static_cast<double>(val.second) / val.first, static_cast<double>(val.first - val.second) / val.first);
    }
    return expectedPoints;
}

int main()
{
    const uint32_t N = 100000000;
    double res = primeGuessing(N);
    std::cout << std::fixed << std::setprecision(8)
            << "PrimeGuessing(" << N << ") = " << res << "\n";
}