# Paradigm-1955C

https://codeforces.com/problemset/problem/1955/C

n
 ships set out to explore the depths of the ocean. The ships are numbered from 1
 to n
 and follow each other in ascending order; the i
-th ship has a durability of ai
.

The Kraken attacked the ships k
 times in a specific order. First, it attacks the first of the ships, then the last, then the first again, and so on.

Each attack by the Kraken reduces the durability of the ship by 1
. When the durability of the ship drops to 0
, it sinks and is no longer subjected to attacks (thus the ship ceases to be the first or last, and the Kraken only attacks the ships that have not yet sunk). If all the ships have sunk, the Kraken has nothing to attack and it swims away.

For example, if n=4
, k=5
, and a=[1,2,4,3]
, the following will happen:

The Kraken attacks the first ship, its durability becomes zero and now a=[2,4,3]
;
The Kraken attacks the last ship, now a=[2,4,2]
;
The Kraken attacks the first ship, now a=[1,4,2]
;
The Kraken attacks the last ship, now a=[1,4,1]
;
The Kraken attacks the first ship, its durability becomes zero and now a=[4,1]
.
How many ships were sunk after the Kraken's attack?

Input
The first line contains an integer t
 (1≤t≤104
) — the number of test cases.

The first line of each test case contains two integers n
 and k
 (1≤n≤2⋅105
, 1≤k≤1015
) — the number of ships and how many times the Kraken will attack the ships.

The second line of each test case contains n
 integers a1,a2,…,an
 (1≤ai≤109
) — the durability of the ships.

It is guaranteed that the sum of n
 for all test cases does not exceed 2⋅105
.

Output
For each test case, output the number of ships sunk by the Kraken on a separate line.
