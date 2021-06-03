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


static vector<uint32_t> calculation(const vector<uint32_t> &A, const vector<uint32_t> &B)
{
    //count how many times given elements appear in the B array
    map<uint32_t, uint32_t> B_map;
    for(const auto & B_elem: B){
        B_map[B_elem]++;
    }

    //rewriting elements of array A to vector C with given condition
    vector<uint32_t> C_vec;
    for(const auto & A_elem: A){
        if(!isPrime(B_map[A_elem]))
            C_vec.push_back(A_elem);
    }
    return C_vec;
}


int main_1(){
    vector<uint32_t> A;
    A.push_back(2);
    A.push_back(3);
    A.push_back(9);
    A.push_back(2);
    A.push_back(5);
    A.push_back(1);
    A.push_back(3);
    A.push_back(7);
    A.push_back(10);

    vector<uint32_t> B;
    B.push_back(2);
    B.push_back(1);
    B.push_back(3);
    B.push_back(4);
    B.push_back(3);
    B.push_back(10);
    B.push_back(6);
    B.push_back(6);
    B.push_back(1);
    B.push_back(7);
    B.push_back(10);
    B.push_back(10);
    B.push_back(10);

    vector<uint32_t> C = calculation(A,B);

    cout << "Print solution :" << endl;
    for(const auto & ans: C){
        cout << ans << endl;
    }
    return 0;
}
