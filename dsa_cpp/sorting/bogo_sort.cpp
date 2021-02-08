/**
 * bogo sort
 * https://en.wikipedia.org/wiki/Bogosort
 *
 * 猴子排序
 */

#include <algorithm>
#include <iostream>
#include <vector>

void bogo_sort(std::vector<int> *array) {
    while (!std::is_sorted(array->begin(), array->end())) {
        std::random_shuffle(array->begin(), array->end());
    }
}

int main() {
    std::vector<int> array{3, 7, 10, 4, 1, 9, 5, 8};
    bogo_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}