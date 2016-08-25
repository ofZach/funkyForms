#pragma once    


#include <thread>
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

#ifdef __GNUG__
static __thread int thread_num;
static __thread int num_threads;
#else
static thread_local int thread_num;
static thread_local int num_threads;
#endif

typedef function <void ()> task;
class thread_pool {
private:
    vector<thread> the_pool;
    
public:
    thread_pool(unsigned int n_threads, task tbd) {
        for(int i = 0; i < n_threads; ++i) {
            the_pool.push_back(thread([=] () {
                thread_num = i;
                num_threads = n_threads;
                tbd();
            }));
        }
    }
    
    void join() {
        for_each(the_pool.begin(), the_pool.end(),
                 [] (thread& t) {t.join();});
    }
    
    void nowait() {
        for_each(the_pool.begin(), the_pool.end(),
                 [] (thread& t) {t.detach();});
    }
    
};

#define parallel_(N) thread_pool (N, []()
#define parallel parallel_(thread::hardware_concurrency())
#define parallel_end ).join();
#define parallel_end_nowait ).nowait();
#define single if(thread_num==0)
#define parallelCap_(N,N2) thread_pool (N, [N2]()