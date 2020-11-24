#include <iostream>                // std::cout
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable

std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
int start_id = 0;

void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
    while (start_id != id) 
        cv.wait(lck); 
    std::cout << "thread " << id << '\n';
    std::cout << "start_id " << start_id << '\n';
    start_id+= 1;
}

void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    start_id = 0;
    cv.notify_all(); // 唤醒所有线程.
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);

    std::cout << "10 threads ready to work...\n";
    go(); // go!

    for (auto& th : threads)
        th.join();

    return 0;
}