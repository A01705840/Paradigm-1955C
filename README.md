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

#### Input
```txt
1
4 6
1 2 4 3
```
```txt
1
2 2
3 2
```
```txt
1
5 20
2 7 1 8 2
```
#### Output 
```txt
3
0
5
```
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
----------------------
![1955c drawio (1)](https://github.com/A01705840/Paradigm-1955C/assets/111139686/fe8e569f-e212-43b6-918a-04f7d2b751c5)

## Implementation
As the problem, was not data heavy, I decided the best program would be OpenMP, since there is not efficiente use of a multicore on the GPU program like CUDA. This is the following code:

```cpp
#include <iostream>
#include <omp.h>
#include <algorithm>

#define SIZE 100000000
using namespace std;

int tests;
int res;

// Acumular los valores para después ingresar en el array
void set_values(int start, int n, int val[]){
    for (int i = start; i < n; i++) {
        std::cin >> val[i];
    }
}

//Se asignan los valores al array
void set_durability(int start, int n, int* arr, int val[]){
    for(int i = start; i < n; i++){
        arr[i] = val[i];
    }
}

//Para poder hace el parallel programming, 
void left_iter(int n, int* arr, int k1, int &local_res){ 
    for (int j = 0; j < n; ++j) {
        if(k1 > arr[j]){
            local_res +=1;
            k1 -= arr[j];
            cout << "left attacks " << k1 << "\n";
        }else if(k1 == arr[j]){
            local_res +=1;
            k1 = 0;
            cout << "left attacks done \n";
        }else if(k1 < arr[j]){
            cout << "left attacks done \n";
        }
    }
}

void right_iter(int n, int* arr, int k2, int &local_res){
    for(int j = 1; j < n; ++j){
        if(k2 > arr[-j]){
            local_res +=1;
            k2 -= arr[-j];
            cout << "right attacks " << k2 << "\n";
        }else if(k2 == arr[-j]){
            local_res +=1;
            k2 = 0;
            cout << "right attacks done \n";
        }else if(k2 < arr[-j]){
            cout << "right attacks done \n";
        }
    }
}

int main() {
    int *arg1 = new int[SIZE];
    std::cin >> tests;

    while (tests != 0) {
        int n, k;
        std::cin >> n >> k;
        int *arr = new int[n];

        int val[n];
        set_values(0, n, val);
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                set_durability(0, n/2, arg1, val);
            }
            #pragma omp section
            {
                set_durability(n/2, n, arg1, val);
            }
        }

        int k1, k2;
        if (k % 2 == 0) {
            k2 = k / 2;
            k1 = k / 2;
            cout << k1 << k2;
        } else {
            k1 = k / 2 + 1;
            k2 = k / 2;
            cout << k1 << k2;
        }

        int local_res_left = 0;
        int local_res_right = 0;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                left_iter(n, arg1, k1, local_res_left);
            }
            #pragma omp section
            {
                right_iter(n, arg1, k2, local_res_right);
            }
        }

        res = local_res_left + local_res_right;

        cout << "res: " << res << endl;
        tests--;
    }
    return 0;
}


```



The function of set_durability(), its funcionality is arraging the input of the ships durability into an array.
```cpp
//Se asignan los valores al array
void set_durability(int start, int n, int* arr, int val[]){
    for(int i = start; i < n; i++){
        arr[i] = val[i];
    }
}
```

Functions for left_iter and right_iter, simulate the attacks of the Kraken when it attacks from the left(last ship) and the right(first ship). These functions are divided to make the parallel programming independent from one another. 

The implementation of parallel programming is shown on 
```cpp
#pragma omp parallel sections
        {
            #pragma omp section
            {
                set_durability(0, n/2, arg1, val);
            }
            #pragma omp section
            {
                set_durability(n/2, n, arg1, val);
            }
        }
```
And
```cpp
#pragma omp parallel sections
        {
            #pragma omp section
            {
                left_iter(n, arg1, k1, local_res_left);
            }
            #pragma omp section
            {
                right_iter(n, arg1, k2, local_res_right);
            }
        }
```

## Time complexity
The complexity on this problem is based on the the worst case scenario. In which both the durability and the amount on attacks is a large number. For example, if the amount of durability is greater than the amount of damage done by the attacks, the the complexity is defined by O(k), k being the attacks. But the situation changes when encountering a situation where the durability is less than the amount of damage done vby the attacks, therefore the time complexity is dependent on the durability being O(a), a being the sum of durability of the ships.

## Citation
CodeForces. (2001). Problem - 1955C - Codeforces Inhabitant of the Deep Sea. Codeforces. Retrieved 23 May. 2024, from https://codeforces.com/problemset/problem/1955/C.

Pankratius, V. (2011). Fundamentals of Multicore Software Development (1st ed.). CRC Press. Retrieved 23 May. 2024, from https://doi.org/https://0-search.ebscohost.com.biblioteca-ils.tec.mx/login.aspx?direct=true.
