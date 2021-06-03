#include <iostream>
#include <map>
#include <cstdint>
#include <vector>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <chrono>
#include <cmath>

using namespace std;

bool isPrime(uint32_t number){
    if (number < 2){
        return false;
    }

    for (uint32_t i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0){
            return false;
        }
    }
    return true;
}

int main_1(){
    uint32_t A[9] = {2,3,9,2,5,1,3,7,10};
    uint32_t B[13] = {2,1,3,4,3,10,6,6,1,7,10,10,10};
    unsigned int B_array_size =  sizeof (B)/sizeof(*B);

    //count how many times given elements appear in the B array
    map<uint32_t, uint32_t> B_map;
    for(unsigned int i = 0; i < B_array_size; i++){
        B_map[B[i]]++;
    }

    //rewriting elements of array A to vector C with given condition
    vector<uint32_t> C_vec;
    for(const auto & A_elem: A){
        if(!isPrime(B_map[A_elem]))
            C_vec.push_back(A_elem);
    }

    cout << "Print solution :" << endl;
    for(const auto & ans: C_vec){
        cout << ans << endl;
    }
    return 0;
}
