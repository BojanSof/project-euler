/*
    1. Get prime divisors of phi
    2. Find e - all coprime numbers with phi by utilizing its prime divisors
    3. For each e, calculate the number of unconcealed messages
    4. Find the minimum number of unconcealed messages
    5. Sum e's that give minimum number of unconcealed messages
    Number of unconcealed messages, dirty and probably not completely correct proof:
    n = p * q, p, q are primes
    m^e = m mod n => (Chinese Remainder Theroem, CRT)
    => m^e = m mod p, and, m^e = m mod q
    m^e = m mod p <=> m^(e-1) = 1 mod p
    If a is primitive element of group Zp, every element is given as a^t, 0 <= t < p.
    This means we can rewrite the congruency as
    a^(t(e-1)) = 1 mod p.
    Fermat's Little Theorem states a^(p-1) = 1 mod p, p is prime, a is integer, so we have
    t(e-1) = 0 mod (p - 1)
    This congruency has GCD(e-1, p-1) solutions.
    The total number of solutions to the congruency m^e = m mod p is 1 + GCD(e-1, p-1).
    We add 1 for the case of m = 0.
    Same goes for m^e = m mod q, so the number of solutions for m^e = m mod n is
    [1 + GCD(e-1,p-1)][1 + GCD(e-1,q-1)]
    We can optimize even further if we notice that the minimum number of messages
    is 9, as GCD(e-1,p-1) or GCD(e-1,q-1) can minimally be 2, as they are even numbers.
    The messages m = 0, m = 1 and m = n - 1 are always unconcealed for example.
*/
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <unordered_set>
#include <utility>

using ullong = unsigned long long;

std::unordered_set<ullong> getPrimeDivisors(const ullong num)
{
    std::unordered_set<ullong> divisors;
    ullong numMut = num;
    while(numMut % 2 == 0)
    {
        divisors.insert(2);
        numMut /= 2;
    }
    for(ullong i = 3; i * i <= num; i += 2)
    {
        while(numMut % i == 0)
        {
            divisors.insert(i);
            numMut /= i;
        }
    }
    return divisors;
}

std::vector<ullong> getCoprimeNumsInRange(ullong rangeMin, ullong rangeMax, ullong num, const std::unordered_set<ullong> numPrimeDivisors)
{
    std::vector<ullong> coprimeNums;
    for(ullong i = rangeMin; i <= rangeMax; ++i)
    {
        bool isCoprime = true;
        for(const auto divisor: numPrimeDivisors)
        {
            if(i % divisor == 0)
            {
                isCoprime = false;
                break;
            }
        }
        if(isCoprime)
        {
            coprimeNums.push_back(i);
        }
    }
    return coprimeNums;
}

ullong gcd(ullong a, ullong b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}

ullong getNumUnconcealedMessages(ullong e, ullong p, ullong q)
{
    return (1 + gcd(e - 1, p - 1)) * (1 + gcd(e - 1, q - 1));
}

ullong rsaEncryption(const ullong p, const ullong q)
{
    const ullong n = p * q;
    const ullong phi = (p - 1) * (q - 1);
    const auto primeDivisors = getPrimeDivisors(phi);
    const auto es = getCoprimeNumsInRange(2, phi - 1, phi, primeDivisors);
    std::map<ullong, ullong> numUnconcealedMsgs;
    for(const auto e: es)
    {
        numUnconcealedMsgs[e] = getNumUnconcealedMessages(e, p, q);
    }
    const auto minNumUnconcealedMsgs = std::min_element(
                numUnconcealedMsgs.begin(), numUnconcealedMsgs.end(), 
                [](const auto& l, const auto& r) { return l.second < r.second; })->second;
    ullong sum = 0;
    for(const auto e: es)
    {
        if(numUnconcealedMsgs[e] == minNumUnconcealedMsgs)
        {
            sum += e;
        }
    }
    return sum;
}

int main()
{
    const ullong p = 1009, q = 3643l;
    const ullong sum = rsaEncryption(p, q);
    std::cout << "RSAEncryption(" << p << ", " << q << ") = " << sum << "\n";
    return 0;
}