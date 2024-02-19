/*
    Let's say we want to reach TARGET sum using the given coins:
    1p, 2p, 5p, 10p, 20p, 50p, 100p, 200p
    TARGET=1p - 1 way [(1p)]
    TARGET=2p - 2 ways [(1p + 1p), (2p)]
    TARGET=3p - 2 ways [(1p + 1p + 1p), (2p + 1p)]
    TARGET=4p - 3 ways [(1p + 1p + 1p + 1p), (1p + 1p + 2p), (2p + 2p)]
    TARGET=5p - 4 ways [(1p + 1p + 1p + 1p), (1p + 1p + 1p + 2p), (1p + 2p + 2p), (5p)]

    Dynamic programming: We create table representing how many ways we can create
    the TARGET by utilizing coins <= COIN.
    | TARGET | 1p | 1p, 2p | 1p, 2p, 5p | ....
    |   1    | 1  |    1   |     1      | ...
    |   2    | 1  |    2   |     2      | ...
    |   3    | 1  |    2   |     2      | ...
    |   4    | 1  |    3   |     3      | ...
    |   5    | 1  |    3   |     4      | ...

    To create TARGET using coins <= COIN, we can refer in the table to find
    the previously calculated number of ways for representing TARGET - COIN using
    coins <= COIN.
    The number of ways is equal to the previously calculated number of ways for
    coins <= PREV_COIN and the number of ways for representing TARGET - COIN using
    coins <= COIN (same column as current, smaller row).
    If TARGET - COIN = 0, then just add 1, as the TARGET can be made using 1 COIN.
    Let's say we have function N(TARGET, COIN) represesnting the ways of making
    TARGET using coins <= COIN.
    Examples:
        N(4p, 2p) = N(4p, 1p) + N(4p - 2p, 2p) = 1 + 2 = 3
        N(5p, 5p) = N(5p, 2p) + 1 = N(5p, 1p) + N(5p - 2p, 2p) + 1 = 1 + 2 + 1 = 4
*/
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

unsigned int coinSums(const unsigned int targetVal)
{
    std::vector<unsigned int> coins{1, 2, 5, 10, 20, 50, 100, 200};
    std::vector<std::vector<unsigned int>> table(targetVal + 1, std::vector<unsigned int>(8, 1));
    for(unsigned int target = 1; target <= targetVal; ++target)
    {
        // there is only one way to create target using 1p, skip that
        for(unsigned int iCoin = 1; iCoin < coins.size(); ++iCoin)
        {
            table[target][iCoin] = table[target][iCoin - 1];
            if(coins[iCoin] <= target)
            {
                if(target == coins[iCoin])
                {
                    table[target][iCoin] += 1;
                }
                else
                {
                    table[target][iCoin] += table[target - coins[iCoin]][iCoin];
                }
            }
        }
    }
    return table[targetVal][coins.size() - 1];
}

int main()
{
    const unsigned int target = 200;
    const unsigned int numWays = coinSums(target);
    std::cout << "CoinSums(" << target << ") = " << numWays << "\n";
    return 0;
}