/**
 * Suppose you are given the following code:
 * class ZeroEvenOdd {
 *   public ZeroEvenOdd(int n) { ... }      // constructor
 *   public void zero(printNumber) { ... }  // only output 0's
 *   public void even(printNumber) { ... }  // only output even numbers
 *   public void odd(printNumber) { ... }   // only output odd numbers
 * }
 * The same instance of ZeroEvenOdd will be passed to three different threads:
 * Thread A will call zero() which should only output 0's.
 * Thread B will call even() which should only ouput even numbers.
 * Thread C will call odd() which should only output odd numbers.
 * Each of the threads is given a printNumber method to output an integer. Modify the given program
 * to output the series 010203040506... where the length of the series must be 2n.
 * Example 1:
 * Input: n = 2
 * Output: "0102"
 * Explanation: There are three threads being fired asynchronously. One of them calls zero(), the
 * other calls even(), and the last one calls odd(). "0102" is the correct output.
 * Example 2:
 * Input: n = 5
 * Output: "0102030405"
 */

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

// WA ??? 这题有判题有 bug 吧
class ZeroEvenOdd {
private:
    int n;
    std::condition_variable cv;
    std::mutex mtx;
    int state;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        this->state = 0;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        for (int i = 1; i <= n; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return this->state == 0; });
            printNumber(0);
            state = i;
            cv.notify_all();
        }
    }

    void even(std::function<void(int)> printNumber) {
        int end = (n + 1) / 2;
        for (int i = 1; i <= end; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (this->state % 2) == 1; });
            printNumber(state);
            state = 0;
            cv.notify_all();
        }
    }

    void odd(std::function<void(int)> printNumber) {
        int end = n / 2;
        for (int i = 1; i <= end; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (this->state != 0) && ((this->state % 2) == 0); });
            printNumber(state);
            state = 0;
            cv.notify_all();
        }
    }
};

int main() {
    auto printNumber = [](int n) { std::cout << n; };
    auto execute = [&](int n) {
        ZeroEvenOdd zeo{n};
        std::thread zero(&ZeroEvenOdd::zero, &zeo, printNumber);
        std::thread even(&ZeroEvenOdd::even, &zeo, printNumber);
        std::thread odd(&ZeroEvenOdd::odd, &zeo, printNumber);

        zero.join();
        even.join();
        odd.join();
    };

    execute(2);
    std::cout << std::endl;
}