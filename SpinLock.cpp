#include <thread>
#include <iostream>
#include <atomic>


class SpinLock {
public:
    SpinLock() {}

    void lock() {
        retries = 0;
        while (flag.test_and_set(std::memory_order_acquire)) {
            // spin until the lock is released
            backoff();
            retries++;
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }

private:
    void backoff() {
        const int max_retries = 8;
        if (retries < max_retries) {
            std::this_thread::yield();
        } else {
            auto delay = std::chrono::microseconds(1 << (retries - max_retries));
            std::this_thread::sleep_for(delay);
        }
    }

    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    int retries{0};
};

SpinLock locker;


void action1() {
    locker.lock();
    std::cout << "action1\n";
    locker.unlock();
}
void action2() {
    locker.lock();
    std::cout << "action2\n";
    locker.unlock();
}

int main(int argc, char *argv[]) {
    std::thread t1(&action1);
    std::thread t2(&action2);
    t1.join();
    t2.join();
    return 0;
}
