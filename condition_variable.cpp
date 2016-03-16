// condition_variable.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
 
int main()
{
    queue<int> produced_nums;
    mutex m;
    condition_variable cond_var;

    bool done = false;
    bool notified = false;
 
    thread producer([&]() {
        for ( int i = 0; i < 20; ++i) {
            this_thread::sleep_for(std::chrono::milliseconds(10));
            unique_lock<mutex> lock(m);  //May lock mutex after construction, unlock before destruction.
            cout << "Producing " << i << endl;
            produced_nums.push(i);            
			cond_var.notify_one();
			notified = true;
        }  
 
        done = true;
        cond_var.notify_one();
    });

    thread consumer([&]() {
        while (!done) {
			this_thread::sleep_for(std::chrono::milliseconds(30));
            unique_lock<mutex> lock(m);
            while (!notified) {  // loop to avoid spurious wakeups
                cond_var.wait(lock);
            }  
            while (!produced_nums.empty()) {
                cout << "------Consuming " << produced_nums.front() << endl;
                produced_nums.pop();
            }  
            notified = false;
        }  
    });
 
    producer.join();
    consumer.join();

    return 0;
}
