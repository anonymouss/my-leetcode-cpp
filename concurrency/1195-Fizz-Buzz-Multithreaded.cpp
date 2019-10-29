/**
 * Write a program that outputs the string representation of numbers from 1 to n, however:
 * If the number is divisible by 3, output "fizz".
 * If the number is divisible by 5, output "buzz".
 * If the number is divisible by both 3 and 5, output "fizzbuzz".
 * For example, for n = 15, we output: 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13,
 * 14, fizzbuzz.
 * Suppose you are given the following code:
 * class FizzBuzz {
 *   public FizzBuzz(int n) { ... }               // constructor
 *   public void fizz(printFizz) { ... }          // only output "fizz"
 *   public void buzz(printBuzz) { ... }          // only output "buzz"
 *   public void fizzbuzz(printFizzBuzz) { ... }  // only output "fizzbuzz"
 *   public void number(printNumber) { ... }      // only output the numbers
 * }
 * Implement a multithreaded version of FizzBuzz with four threads. The same instance of FizzBuzz
 * will be passed to four different threads:
 * Thread A will call fizz() to check for divisibility of 3 and outputs fizz.
 * Thread B will call buzz() to check for divisibility of 5 and outputs buzz.
 * Thread C will call fizzbuzz() to check for divisibility of 3 and 5 and outputs fizzbuzz.
 * Thread D will call number() which should only output the numbers.
 */

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class FizzBuzz {
private:
    int n;
    int i;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        i = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz) {
        while (i <= n) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 == 0 && i % 5 != 0) || (i > n); });
            if (i <= n) {
                printFizz();
                ++i;
            }
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz) {
        while (i <= n) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 != 0 && i % 5 == 0) || (i > n); });
            if (i <= n) {
                printBuzz();
                ++i;
            }
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz) {
        while (i <= n) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 == 0 && i % 5 == 0) || (i > n); });
            if (i <= n) {
                printFizzBuzz();
                ++i;
            }
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber) {
        while (i <= n) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 != 0 && i % 5 != 0) || (i > n); });
            if (i <= n) {
                printNumber(i);
                ++i;
            }
            cv.notify_all();
        }
    }
};

int main() {
    auto printNumber = [](int n) { std::cout << n << ", "; };
    auto printFizz = []() { std::cout << "Fizz, "; };
    auto printBuzz = []() { std::cout << "Buzz, "; };
    auto printFizzBuzz = []() { std::cout << "FizzBuzz, "; };

    auto execute = [&](int n) {
        FizzBuzz fb{n};
        std::thread t1(&FizzBuzz::fizz, &fb, printFizz);
        std::thread t2(&FizzBuzz::buzz, &fb, printBuzz);
        std::thread t3(&FizzBuzz::fizzbuzz, &fb, printFizzBuzz);
        std::thread t4(&FizzBuzz::number, &fb, printNumber);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    };

    execute(15);
    std::cout << std::endl;
}