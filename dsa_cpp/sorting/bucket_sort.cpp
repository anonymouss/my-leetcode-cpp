/**
 * Bucket sort
 * https://en.wikipedia.org/wiki/Bucket_sort
 */

#include <iostream>
#include <vector>

void bucket_sort(std::vector<int> *array) {
    auto min = (*array)[0];
    auto max = min;
    for (const auto &e : *array) {
        if (min > e) min = e;
        if (max < e) max = e;
    }

    // 构建空桶
    auto range = max - min + 1;
    std::vector<std::vector<int>> buckets(range, std::vector<int>{});

    // 放入桶
    for (const auto &e : *array) {
        buckets[e - min].emplace_back(e);
    }

    // 从桶中恢复
    int index = 0;
    for (const auto &bucket : buckets) {
        for (const auto &e : bucket) {
            (*array)[index++] = e;
        }
    }
}

int main() {
    std::vector<int> array{3, 7, 10, 4, 1, 9, 5, 8};
    bucket_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}