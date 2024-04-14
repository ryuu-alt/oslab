
/*
 * DEMONSTRATION OF READER WRITER PROBLEM
 *
 * SUBMISSION BY ADITYA KUMAR
 * 2K22/CO/26
 * 
*/

#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
using namespace std;

int shared_data = 0;
counting_semaphore<1> access_to_data(1);
counting_semaphore<1> read_count_access(1);
int read_count = 0;

void reader(int id) {
    for (int i = 0; i < 5; ++i) {
        read_count_access.acquire();
        read_count++;
        if (read_count == 1)  access_to_data.acquire();
		printf("Reader %d enters. Read count = %d.\n", id, read_count);
        read_count_access.release();

        printf("Reader %d reads data = %d\n", id, shared_data);

        read_count_access.acquire();
		printf("Reader %d leaves. Read count = %d.\n", id, read_count);
        read_count--;
        if (read_count == 0) access_to_data.release();
        read_count_access.release();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void writer(int id) {
    for (int i = 0; i < 5; ++i) {
        access_to_data.acquire();
		read_count_access.acquire();
        
        shared_data++;
        printf("Writer %d writes data = %d. Read count is %d.\n", id, shared_data, read_count);
        
		read_count_access.release();
        access_to_data.release();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    vector<thread> threads;
    
    for (int i = 0; i < 5; ++i)
        threads.push_back(thread(reader, i));
    for (int i = 0; i < 2; ++i)
        threads.push_back(thread(writer, i));

    for (auto& th : threads) th.join();

    return 0;
}
