/**
 * Suppose we have a class:
 * public class Foo {
 *   public void first() { print("first"); }
 *   public void second() { print("second"); }
 *   public void third() { print("third"); }
 * }
 * The same instance of Foo will be passed to three different threads. Thread A will call first(),
 * thread B will call second(), and thread C will call third(). Design a mechanism and modify the
 * program to ensure that second() is executed after first(), and third() is executed after second().
 * Example 1:
 * Input: [1,2,3]
 * Output: "firstsecondthird"
 * Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread
 * A calls first(), thread B calls second(), and thread C calls third(). "firstsecondthird" is the
 * correct output.
 * Example 2:
 * Input: [1,3,2]
 * Output: "firstsecondthird"
 * Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread
 * C calls second(). "firstsecondthird" is the correct output.
 * Note:
 * We do not know how the threads will be scheduled in the operating system, even though the numbers
 * in the input seems to imply the ordering. The input format you see is mainly to ensure our tests'
 * comprehensiveness.
*/

#include <functional>
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>

class Foo {
public:
    Foo() : next(0) {}

    void first(std::function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        std::unique_lock<std::mutex> lock(mtx);
        printFirst(); 
        next = 2;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return this->next == 2; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        next = 3;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return this->next == 3; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int next;
};

int main() {
    auto printFirst = []() { std::cout << "first" << std::endl; };
    auto printSecond = []() { std::cout << "second" << std::endl; };
    auto printThird = []() { std::cout << "third" << std::endl; };


    auto execute = [&](const std::vector<int> &vec) {
        Foo foo;
        std::thread t1, t2, t3;
        for(const auto &id : vec) {
            if (id == 1) {
                t1 = std::thread{&Foo::first, &foo, printFirst};
            } else if (id == 2) {
                t2 = std::thread{&Foo::second, &foo, printSecond};
            } else if (id == 3) {
                t3 = std::thread{&Foo::third, &foo, printThird};
            }
        }
        t1.join(); t2.join(); t3.join();
    };

    execute({1, 3, 2});
}