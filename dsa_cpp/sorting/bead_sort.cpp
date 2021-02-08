/**
 * bead sort
 * https://en.wikipedia.org/wiki/Bead_sort
 *
 * 模拟珠子掉落
 * 假设N个数字排序，最大数字为M，则模拟构建M条线，串上珠子。每条线的同一行对应一个待排序数字，一共N行。
 * 即，如果第5个数字为3，则第五行的前三条线对应位置有珠子，其他线第五行没有珠子。串完之后，珠子随重力下落。
 * 然后从各行数珠子恢复结果，则为已排序数组。
 */

#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>

void bead_sort(std::vector<int> *array) {
    auto max_rows = array->size();; // make it readable
    int max_cols = (*array)[0];
    for (auto row = 1; row < max_rows; ++row) {
        if ((*array)[row] > max_cols) {
            max_cols = (*array)[row];
        }
    }

    uint8_t *beads = new uint8_t[max_cols * max_rows];
    memset(beads, 0, max_cols * max_rows);

    auto get_bead_at = [&](int row, int col) {
        return &beads[row * max_cols + col];
    };

    // construct initial beads from original array
    for (auto row = 0; row < max_rows; ++row) {
        for (auto col = 0; col < (*array)[row]; ++col) {
            *get_bead_at(row, col) = 1;
        }
    }

    // beads falling down
    for (auto col = 0; col < max_cols; ++col) {
        auto beads_in_row = 0;
        for (auto row = 0; row < max_rows; ++row) {
            auto *bead = get_bead_at(row, col);
            beads_in_row += static_cast<int>(*bead);
            *bead = 0;
        }

        for (auto row = max_rows - beads_in_row; row < max_rows; ++row) {
            *get_bead_at(row, col) = 1;
        }
    }

    // recover array from beads after falling down
    for (auto row = 0; row < max_rows; ++row) {
        auto col = 0;
        // for (; col < max_cols && *get_bead_at(row, col) == 1; ++col)
        while (col < max_cols && *get_bead_at(row, col) == 1) {
            ++col;
        }
        (*array)[row] = col;
    }

    delete [] beads;
}

int main() {
    std::vector<int> array{5, 3, 1, 7, 4, 1, 1, 20};

    bead_sort(&array);

    for (const auto &e : array) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}