/**
 * bitonic sort
 * https://en.wikipedia.org/wiki/Bitonic_sorter
 *
 * 主要分为两步：
 * 1. 生成双调序列：自下而上的进行双调合并，从最小的两个单个元素序列开始
 * 2. 双调排序：自上而下的将双调序列平分后分别排序，直至最小两个元素
 */

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

enum MONO : uint32_t {
    ERROR,
    INC,
    DEC,
};

MONO rev(MONO dir) {
    switch (dir) {
        case MONO::INC: return MONO::DEC;
        case MONO::DEC: return MONO::INC;
        default: return MONO::ERROR;
    }
}

void bitonic_merge(std::vector<int> *array, uint32_t floor, uint32_t up, MONO dir) {
    if (up <= floor || up - floor == 1) {
        return;
    }

    auto process = [&](uint32_t i, uint32_t j) {
        if ((((*array)[i] > (*array)[j]) && dir == MONO::INC)
                || (((*array)[i] < (*array)[j]) && dir == MONO::DEC)) {
            std::iter_swap(array->begin() + i, array->begin() + j);
        }
    };

    auto mid = (up - floor) / 2;
    for (int i = floor; i < floor + mid; ++i) {
        process(i, i + mid);
    }
    bitonic_merge(array, floor, floor + mid, dir);
    bitonic_merge(array, floor + mid, up, dir);
}

void bitonic_sort(std::vector<int> *array, uint32_t floor, uint32_t up, MONO dir) {
    if (up <= floor || up - floor == 1) {
        return;
    }

    auto mid = (up - floor) / 2;
    bitonic_sort(array, floor, floor + mid, dir);
    bitonic_sort(array, floor + mid, up, rev(dir));

    bitonic_merge(array, floor, up, dir);
}

// bitnoic sort wrapper
void sort(std::vector<int> *array, MONO dir) {
    bitonic_sort(array, 0, array->size(), dir);
}

int main() {
    std::vector<int>array{3, 7, 4, 8, 6, 2, 1, 5};

    sort(&array, MONO::DEC);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}