#include <iostream>
#include <vector>
using namespace std;

int main() {
    int tests;
    int res;
    std::cin >> tests;

    while (tests != 0) {
        int n, k;
        std::cin >> n >> k;

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        //std::cout << k%2 << std::endl;
        int k1;
        int k2;
        if (k%2 == 0) {
            k2 = k/2;
            k1 = k/2;
            //std::cout << "k1: " << k1 << ", k2: " << k2 << std::endl;
        } else if (k%2 != 0) {
            k1 = k/2 + 1;
            k2 = k/2;
            //std::cout << "k1: " << k1 << ", k2: " << k2 << std::endl;
        }

        for (int j = 0; j < n; ++j) {
            if(k1 > arr[j]){
                res +=1;
                k1 -= arr[j];
            }else if(k1 == arr[j]){
                res +=1;
                k1 = 0;
                break;
            }else if(k1 < arr[j]){
                break;
            }
        }
        for(int j = 1; j < n; ++j){
            if(k2 > arr[-j]){
                res +=1;
                k2 -= arr[-j];
            }else if(k2 == arr[-j]){
                res +=1;
                k2 = 0;
                break;
            }else if(k2 < arr[-j]){
                break;
            }
        }
        //cout << "res: " << res << endl;
        tests--;
        return res;
    }
    return 0;
}