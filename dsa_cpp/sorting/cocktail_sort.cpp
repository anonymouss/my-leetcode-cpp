/**
 * crocktail sort
 * https://en.wikipedia.org/wiki/Cocktail_shaker_sort
 *
 * 鸡尾酒排序：双向冒泡
 * 时间：O(n^2)
 */

#include <iostream>
#include <vector>
#include <algorithm>

void cocktail_sort(std::vector<int> *array) {
    std::size_t bottom = 0, top = array->size();
    bool already_sorted = false;

    while (!already_sorted) {
        already_sorted = true;
        for (auto i = bottom; i < top - 1; ++i) {
            if ((*array)[i] > (*array)[i + 1]) {
                std::iter_swap(array->begin() + i, array->begin() + i + 1);
                already_sorted = false;
            }
        }
        --top;

        for (auto j = top - 1; j > 0; --j) {
            if ((*array)[j] < (*array)[j - 1]) {
                std::iter_swap(array->begin() + j, array->begin() + j - 1);
                already_sorted = false;
            }
        }
        ++bottom;
    }
}

int main() {
    std::vector<int> array{3, 7, 10, 4, 1, 9, 5, 8};
    cocktail_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}