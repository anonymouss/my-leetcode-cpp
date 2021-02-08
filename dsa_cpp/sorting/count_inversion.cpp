/*
 * https://www.cp.eng.chula.ac.th/~prabhas//teaching/algo/algo2008/count-inv.htm
 * T(n) = O(n long n)
 */

#include <vector>
#include <iostream>
#include <algorithm>

void draw(const std::vector<int> &array) {
    auto H = *std::max_element(array.cbegin(), array.cend()), W = static_cast<int>(array.size());
    std::cout << std::endl;
    for (auto h = 0; h < H; ++h) {
        for (auto w = 0; w < W; ++w) {
            if (array[w] >= (H - h)) {
                std::cout << ".";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int merge_and_count(const std::vector<int> &array, std::vector<int> *c) {
    auto mid = array.size() / 2;
    auto ita = array.begin(), itb = array.begin() + mid, enda = itb, endb = array.end();
    int count = 0;

    while (ita != enda && itb != endb) {
        auto a = *ita, b = *itb;
        if (a < b) {
            c->emplace_back(a);
            ++ita;
        } else {
            c->emplace_back(b);
            ++itb;
            count += std::distance(ita, enda);
        }
    }
    return count;
}

int sort_and_count(const std::vector<int> &array, std::vector<int> *c) {
    if (array.size() <= 1) {
        return 0;
    }

    auto mid = array.size() / 2;
    int count = 0;

    count += sort_and_count(std::vector<int>{array.begin(), array.begin() + mid}, c);
    count += sort_and_count(std::vector<int>{array.begin() + mid, array.end()}, c);

    count += merge_and_count(array, c);

    return count;
}

int get_count_inversion(const std::vector<int> &array) {
    draw(array);
    std::vector<int> c;
    return sort_and_count(array, &c);
}

int main() {
    std::vector<std::vector<int>> arrays{
            {2, 4, 1, 3, 5}, // 3
            {100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, // 4950
             83,  82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,
             66,  65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
             49,  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
             32,  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
             15,  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1}
    };

    for (const auto &array : arrays) {
        std::cout << "count inversion : " << get_count_inversion(array) << std::endl;
    }
}