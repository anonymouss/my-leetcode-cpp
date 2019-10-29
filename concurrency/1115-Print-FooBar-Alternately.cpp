/**
 * Suppose you are given the following code:
 * class FooBar {
 *   public void foo() {
 *     for (int i = 0; i < n; i++) {
 *       print("foo");
 *     }
 *   }
 *   public void bar() {
 *     for (int i = 0; i < n; i++) {
 *       print("bar");
 *     }
 *   }
 * }
 * The same instance of FooBar will be passed to two different threads. Thread A will call foo()
 * while thread B will call bar(). Modify the given program to output "foobar" n times.
 * Example 1:
 * Input: n = 1
 * Output: "foobar"
 * Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the
 * other calls bar(). "foobar" is being output 1 time.
 * Example 2:
 * Input: n = 2
 * Output: "foobarfoobar"
 * Explanation: "foobar" is being output 2 times.
 */

#include <functional>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>

class FooBar {
private:
    int n;
    std::condition_variable cv;
    std::mutex mtx;
    int state;

public:
    FooBar(int n) {
        this->n = n;
        this->state = 0;
    }

    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return this->state == 0; });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            ++state;
            cv.notify_all();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return this->state == 1; });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            --state;
            cv.notify_all();
        }
    }
};

int main() {
    auto printFoo = []() { std::cout << "foo"; };
    auto printBar = []() { std::cout << "bar"; };

    auto execute = [&](int n) {
        FooBar fb{n};
        std::thread tf(&FooBar::foo, &fb, printFoo);
        std::thread tb(&FooBar::bar, &fb, printBar);
        tf.join();
        tb.join();
    };

    execute(5);
    std::cout << std::endl;
}