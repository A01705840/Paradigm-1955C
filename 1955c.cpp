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
