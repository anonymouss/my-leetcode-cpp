#ifndef __UTILS_MY_CONTAINER_UTIL__
#define __UTILS_MY_CONTAINER_UTIL__

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief display elements of 1-D vector
 *
 * object of type T must be printable
 */
template<typename T>
void myDispVector1D(const vector<T> &vec1D, int padding = 0) {
    std::cout <<  string(padding, ' ') << "[";
    for (const auto &e : vec1D) {
        std::cout << e << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief display elements of 2-D vector
 *
 * object of type T must be printable
 */
template<typename T>
void myDispVector2D(const vector<vector<T>> &vec2D, int padding = 2) {
    auto paddingStr = string(padding, ' ');
    std::cout << paddingStr << "[\n";
    for (const auto &vec1D : vec2D) {
        myDispVector1D(vec1D, padding+2);
    }
    std::cout << paddingStr << "]" << std::endl;
}

#endif // __UTILS_MY_CONTAINER_UTIL__