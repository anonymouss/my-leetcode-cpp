/**
 * Bubble sort
 * https://en.wikipedia.org/wiki/Bubble_sort
 * 
 * 冒泡排序
 * 时间复杂度 O(n^2)，最优O(n)
 * 空间复杂度O(n)，辅助空间O(1)
 */

#include <iostream>
#include <vector>

void bubble_sort(std::vector<int> *array) {
    auto size = array->size();
    bool already_sorted = false; // break loop if remaining elements are already sorted
    for (auto i = 0; (i < size) && !already_sorted; ++i) {
        already_sorted = true;
        for (auto j = 0; j < size - i - 1; ++j) {
            if ((*array)[j] > (*array)[j + 1]) {
                already_sorted = false;
                // swap
                auto v = (*array)[j];
                (*array)[j] = (*array)[j + 1];
                (*array)[j + 1] = v;
            }
        }
    }
}

int main() {
    std::vector<int> array{3, 7, 10, 4, 1, 9, 5, 8};
    bubble_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}