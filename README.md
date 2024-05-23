# Paradigm-1955C

## Inhabitant of the Deep Sea
For this evidence, the problem used was 
https://codeforces.com/problemset/problem/1955/C

The problem is as follows, there are n ships on the sea, for each ship (i), the durability is defined by a_i. Suddenly, a Kraken comes out of the sea and attacks the fleet. The pattern of attack is on the this order:
1. The Kraken attacks the first ship.
2. The Kraken attacks the last ship.

*Note: Each blow from the Kraken reduces the durability of the ship by 1.*
The number of attacks make by the Kraken is defined by k, after the attacks end, the Kraken leaves, and only the ships with a durability over 0, are still standing.

¿How many ships has the Kraken taken down after the attack?

## Problem
To understand better the problem, I listed the statements that apply to the behavior of the program.
1. The Kraken only attacks the first and last ship.
2. The Kraken attacks are constant, but not every ship sinks at the same time or with the same amout of attacks.
3. The attacks from the Kraken, if it is an even number are k/2 to the first ships and k/2 to the last ship.
4. Meanwhile uneven amount of attacks are k/2+1 to the first ship and k/2 to the last ship.

## Modal
### Parallel Programming

For the making of the program, I used parallel programming, focusing on the division of the task of filling the durability array and the iteration of attacks on both sides (right_iter & left_iter). In more detail, this parallelism is on the task parallelism pattern, because it dividing the tasks. These tasks can be naturally independent or can be made to be independent from one another. (Pankratius, 2011).
![image](https://github.com/A01705840/Paradigm-1955C/assets/111139686/bcf2ea17-9c87-4f0d-bf99-838e6dfe9b61)
This is how the thread would look like.
![1955c drawio (1)](https://github.com/A01705840/Paradigm-1955C/assets/111139686/fe8e569f-e212-43b6-918a-04f7d2b751c5)

As the problem, was not data heavy, I decided the best program would be OpenMP

## Citation
Pankratius, V. (2011). Fundamentals of Multicore Software Development (1st ed.). CRC Press. Retrieved 23 May. 2024, from https://doi.org/https://0-search.ebscohost.com.biblioteca-ils.tec.mx/login.aspx?direct=true.
