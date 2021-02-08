/**
 * Comb Sort
 * https://en.wikipedia.org/wiki/Comb_sort
 * 梳子排序
 * 冒泡排序的变种，每次gap按照1.3倍缩小
 * 时间：O(n log N) for best case, O(n^2/2^p) for average, O(n^2) for worst
 * 空间：O(1)
 */

#include <vector>
#include <iostream>
#include <algorithm>

std::size_t get_next_gap(std::size_t gap) {
    return gap = gap * 10 / 13;
}

void comb_sort(std::vector<int> *array) {
    auto gap = get_next_gap(array->size());

    while (gap > 0) {
        for (auto i = 0; i + gap < array->size(); ++i) {
            if ((*array)[i] > (*array)[i + gap]) {
                std::iter_swap(array->begin() + i, array->begin() + i + gap);
            }
        }
        gap = get_next_gap(gap);
    }
}

int main() {
    std::vector<int> array{3, 7, 10, 4, 1, 9, 5, 8};
    comb_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}
