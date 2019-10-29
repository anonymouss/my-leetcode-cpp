/**
 * There are two kinds of threads, oxygen and hydrogen. Your goal is to group these threads to form
 * water molecules. There is a barrier where each thread has to wait until a complete molecule can
 * be formed. Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods
 * respectively, which will allow them to pass the barrier. These threads should pass the barrier
 * in groups of three, and they must be able to immediately bond with each other to form a water
 * molecule. You must guarantee that all the threads from one molecule bond before any other threads
 * from the next molecule do.
 * In other words:
 * If an oxygen thread arrives at the barrier when no hydrogen threads are present, it has to wait
 * for two hydrogen threads.
 * If a hydrogen thread arrives at the barrier when no other threads are present, it has to wait for
 * an oxygen thread and another hydrogen thread.
 * We don’t have to worry about matching the threads up explicitly; that is, the threads do not
 * necessarily know which other threads they are paired up with. The key is just that threads pass
 * the barrier in complete sets; thus, if we examine the sequence of threads that bond and divide
 * them into groups of three, each group should contain one oxygen and two hydrogen threads.
 * Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.
 * Example 1:
 * Input: "HOH"
 * Output: "HHO"
 * Explanation: "HOH" and "OHH" are also valid answers.
 * Example 2:
 * Input: "OOHHHH"
 * Output: "HHOHHO"
 * Explanation: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" and "OHHOHH"
 * are also valid answers.
 * Constraints:
 * Total length of input string will be 3n, where 1 ≤ n ≤ 20.
 * Total number of H will be 2n in the input string.
 * Total number of O will be n in the input string.
 */

#include <functional>
#include <mutex>
#include <thread>

class H2O {
public:
    H2O() : hydrogens(0) {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return this->hydrogens > 0; });
        releaseHydrogen();
        --hydrogens;
        cv.notify_all();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        // releaseOxygen() outputs "O". Do not change or remove this line.
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return this->hydrogens == 0; });
        releaseOxygen();
        hydrogens += 2;
        cv.notify_all();
    }

private:
    int hydrogens;
    std::mutex mtx;
    std::condition_variable cv;
};

int main() {}