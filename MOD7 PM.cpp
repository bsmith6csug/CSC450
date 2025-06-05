#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int counter = 0;
std::mutex mtx;
std::condition_variable cv;
bool first_thread_finished = false;

void countUp() {
    for (int i = 1; i <= 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lock(mtx);
            counter = i;
            std::cout << "Up Thread: " << counter << std::endl;
        }
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        first_thread_finished = true;
        std::cout << "--- Finished Counting Up ---" << std::endl;
    }
    cv.notify_one();
}


void countDown() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return first_thread_finished; });

    std::cout << "--- Counting Down ---" << std::endl;
    while (counter >= 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::cout << "Down Thread: " << counter << std::endl;
        counter--;
    }
}

int main() {
    std::cout << "--- Counting Up ---" << std::endl;

    std::thread upThread(countUp);
    std::thread downThread(countDown);

    upThread.join();
    downThread.join();

    std::cout << "Up Thread and Down Thread Have Finished!" << std::endl;

    return 0;
}
