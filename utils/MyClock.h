#ifndef __UTILS_MY_CLOCK__
#define __UTILS_MY_CLOCK__

#include <chrono>
#include <ratio>
#include <iostream>
#include <string>
#include <iomanip>

using MY_NS = std::nano;
using MY_US = std::micro;
using MY_MS = std::milli;
using MY_SEC = std::ratio<1, 1>;
using MY_TP = std::chrono::system_clock::time_point;

inline MY_TP MyGetTimestampNow() {
    return std::chrono::system_clock::now();
}

template<typename T>
class MyClock {
public:
    MyClock() {
        std::cout << "Entering function..." << std::endl;
        mStartPoint = MyGetTimestampNow();
    }

    ~MyClock() {
        mEndPoint = MyGetTimestampNow();
        //auto mDuration = std::chrono::duration_cast<T>(mEndPoint - mStartPoint);
        std::chrono::duration<double, T> duration = mEndPoint - mStartPoint;
        std::cout << "Exiting function... " << duration.count() << toStr() << " elapsed." << std::endl;
    }

private:
    std::string toStr() const {
        if (std::is_same<T,MY_NS>::value) return " ns";
        else if (std::is_same<T, MY_US>::value) return " us";
        else if (std::is_same<T, MY_MS>::value) return " ms";
        else if (std::is_same<T, MY_SEC>::value) return " s";
        else return " ?";
    }

    MY_TP mStartPoint;
    MY_TP mEndPoint;
};

#endif // __UTILS_MY_CLOCK__
