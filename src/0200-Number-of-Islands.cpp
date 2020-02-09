/**
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is
 * surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You
 * may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 * Output: 1
 *
 * Example 2:
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 * Output: 3
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define DFS_METHOD 0
#define BFS_METHOD 1
#define UNION_FIND 2

#define COMPILE_VERSION UNION_FIND 

#if (COMPILE_VERSION == DFS_METHOD)
class Solution {
public:
    int numIslands(std::vector<std::vector<char>> &grid) {
        auto rows = grid.size();
        if (rows == 0) {
            return 0;
        }
        auto cols = grid[0].size();
        auto islands = 0;
        for (auto r = 0; r < rows; ++r) {
            for (auto c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    dfs(grid, r, c);
                }
            }
        }
        return islands;
    }

private:
    void dfs(std::vector<std::vector<char>> &grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();

        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r-1][c] == '1') dfs(grid, r - 1, c);
        if (r + 1 < rows && grid[r+1][c] == '1') dfs(grid, r + 1, c);
        if (c - 1 >= 0 && grid[r][c-1] == '1') dfs(grid, r, c - 1);
        if (c + 1 < cols && grid[r][c+1] == '1') dfs(grid, r, c + 1);
    }
};
#elif (COMPILE_VERSION == BFS_METHOD)
class Solution {
public:
    int numIslands(std::vector<std::vector<char>> &grid) {
        auto rows = grid.size();
        if (rows == 0) return 0;
        auto cols = grid[0].size();
        auto islands = 0;
        for (auto r = 0; r < rows; ++r) {
            for (auto c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    grid[r][c] = '0';
                    std::queue<std::pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    while (!neighbors.empty()) {
                        auto pos = neighbors.front();
                        neighbors.pop();
                        int r = pos.first, c = pos.second;
                        if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                            grid[r - 1][c] = '0';
                            neighbors.push({r - 1, c});
                        }
                        if (r + 1 < rows && grid[r + 1][c] == '1') {
                            grid[r + 1][c] = '0';
                            neighbors.push({r + 1, c});
                        }
                        if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                            grid[r][c - 1] = '0';
                            neighbors.push({r, c - 1});
                        }
                        if (c + 1 < cols && grid[r][c + 1] == '1') {
                            grid[r][c + 1] = '0';
                            neighbors.push({r, c + 1});
                        }
                    }
                }
            }
        }
        return islands;
    }
};
#elif (COMPILE_VERSION == UNION_FIND)
class UnionFind {
public:
    UnionFind(std::vector<std::vector<char>> &grid) {
        connects = 0;
        auto rows = grid.size();
        auto cols = grid[0].size();
        for (auto r = 0; r < rows; ++r) {
            for (auto c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    parent.emplace_back(r * cols + c);
                    ++connects;
                } else {
                    parent.emplace_back(-1);
                }
                rank.emplace_back(0);
            }
        }
    }

    int find(int i) {
        while (parent[i] != i) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }

    void Union(int a, int b) {
        auto root_a = find(a);
        auto root_b = find(b);
        if (root_a != root_b) {
            if (rank[root_a] > rank[root_b]) {
                parent[root_b] = root_a;
            } else if (rank[root_a] < rank[root_b]) {
                parent[root_a] = root_b;
            } else {
                parent[root_b] = root_a;
                rank[root_a] += 1;
            }
            --connects;
        }
    }

    int getConnects() const {
        return connects;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
    int connects;
};

class Solution {
public:
    int numIslands(std::vector<std::vector<char>> &grid) {
        auto rows = grid.size();
        if (rows == 0) return 0;
        auto cols = grid[0].size();

        UnionFind uf{grid};
        int islands = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                        uf.Union(r * cols + c, (r - 1) * cols + c);
                    }
                    if (r + 1 < rows && grid[r + 1][c] == '1') {
                        uf.Union(r * cols + c, (r + 1) * cols + c);
                    }
                    if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                        uf.Union(r * cols + c, r * cols + c - 1);
                    }
                    if (c + 1 < cols && grid[r][c + 1] == '1') {
                        uf.Union(r * cols + c, r * cols + c + 1);
                    }
                }
            }
        }
        return uf.getConnects();
    }
};
#endif

int main() {
    Solution sln;

    std::vector<std::vector<std::vector<char>>> grids{
        {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        }
    };

    for (auto &grid : grids) {
        TestCount();
        std::cout << sln.numIslands(grid) << std::endl;
    }
}