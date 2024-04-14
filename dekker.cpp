
/*
 * DEMONSTRATION OF DEKKER'S ALGORITHM
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<bool> want1{false};
atomic<bool> want2{false};
atomic<int> turn{1};

void lock1() {
    want1.store(true);
    while (want2.load()) {
        if (turn.load() != 1) {
            want1.store(false);
            while (turn.load() != 1); // Busy wait
            want1.store(true);
        }
    }
}

void unlock1() {
    turn.store(2);
    want1.store(false);
}

void lock2() {
    want2.store(true);
    while (want1.load()) {
        if (turn.load() != 2) {
            want2.store(false);
            while (turn.load() != 2); // Busy wait
            want2.store(true);
        }
    }
}

void unlock2() {
    turn.store(1);
    want2.store(false);
}

void threadFunction1() {
    for (int i = 0; i < 5; ++i) {
        lock1();
        cout << "Thread 1 is in the critical section.\n";
        unlock1();
    }
}

void threadFunction2() {
    for (int i = 0; i < 5; ++i) {
        lock2();
        cout << "Thread 2 is in the critical section.\n";
        unlock2();
    }
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
