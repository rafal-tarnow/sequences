#include <iostream>
#include <map>
#include <cstdint>
#include <vector>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <chrono>
#include <cmath>

using namespace std;

static uint32_t number_to_check = 0;
static uint32_t divisor_to_check = 2;
static uint32_t ret_divisor = 0;
static bool done = false;
static pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

static void * thread(void*)
{
    bool t_done = false;
    uint32_t t_number_to_check = 0;
    uint32_t my_divisor_to_check = 2;

    pthread_mutex_lock(&data_mutex);
    t_number_to_check = number_to_check;
    pthread_mutex_unlock(&data_mutex);

    while(1){
        pthread_mutex_lock(&data_mutex);
        t_done = done;
        my_divisor_to_check = divisor_to_check++;
        pthread_mutex_unlock(&data_mutex);

        if((my_divisor_to_check > sqrt(t_number_to_check)) || (t_done == true)){
            return NULL;
        }
        else if(t_number_to_check % my_divisor_to_check == 0){
            pthread_mutex_lock(&data_mutex);
            done = true;
            ret_divisor = my_divisor_to_check;
            pthread_mutex_unlock(&data_mutex);
            return NULL;
        }
    }
}

static bool isPrime_CachedMultithread(uint32_t A_elem)
{
    //CACHE
    static map<uint32_t, bool> primes_cache;
    if(primes_cache.count(A_elem))
        return primes_cache[A_elem];

    //CHECK PRIME
    if (A_elem < 2){
        primes_cache[A_elem] = false;
        return false;
    }

    const int NTHREADS = 8;
    pthread_t thread_id[NTHREADS];
    int i, j;

    divisor_to_check = 2;
    ret_divisor = 0;
    done = false;
    number_to_check = A_elem;

    for(i=0; i < NTHREADS; i++){
        pthread_create( &thread_id[i], NULL, thread, NULL);
    }

    for(j=0; j < NTHREADS; j++){
        pthread_join( thread_id[j], NULL);
    }

    if(ret_divisor != 0){
        primes_cache[A_elem] = false;
        return false;
    }
    else{
        primes_cache[A_elem] = true;
        return true;
    }
}


int main()
{
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
        if(!isPrime_CachedMultithread(B_map[A_elem]))
            C_vec.push_back(A_elem);
    }

    cout << "Print solution :" << endl;
    for(const auto & ans: C_vec){
        cout << ans << endl;
    }
    return 0;
}
