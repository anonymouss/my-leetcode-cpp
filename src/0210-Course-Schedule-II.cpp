/**
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course
 * 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, return the ordering of
 * courses you should take to finish all courses.
 * There may be multiple correct orders, you just need to return one of them. If it is impossible to
 * finish all courses, return an empty array.
 *
 * Example 1:
 * Input: 2, [[1,0]] 
 * Output: [0,1]
 * Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
 *              course 0. So the correct course order is [0,1] .
 *
 * Example 2:
 * Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 * Explanation: There are a total of 4 courses to take. To take course 3 you should have finished
 *              both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course
 *              0. So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
 *
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read
 * more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input prerequisites.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

#define IN_DEGREE 0
#define DFS 1

#define COMPILE_VERSION DFS

// https://leetcode-cn.com/problems/course-schedule-ii/solution/ke-cheng-biao-ii-by-leetcode/
#if (COMPILE_VERSION == IN_DEGREE)
class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        std::unordered_map<int, std::vector<int>> adjList;
        std::vector<int> indegree(numCourses);
        std::vector<int> topologicalOrder(numCourses);

        for (auto i = 0; i < prerequisites.size(); ++i) {
            auto dst = prerequisites[i][0];
            auto src = prerequisites[i][1];
            if (adjList.find(src) != adjList.end()) {
                adjList[src].emplace_back(dst);
            } else {
                std::vector<int> lst{dst};
                adjList.emplace(std::make_pair(src, lst));
            }
            indegree[dst] += 1;
        }

        std::queue<int> queue;
        for (auto i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                queue.emplace(i);
            }
        }

        auto i = 0;
        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            topologicalOrder[i++] = node;
            if (adjList.count(node) != 0) {
                for (auto neighbor : adjList[node]) {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        queue.emplace(neighbor);
                    }
                }
            }
        }
    
        if (i == numCourses) {
            return topologicalOrder;
        }
        return {};
    }
};
#elif (COMPILE_VERSION == DFS)
class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        init(numCourses);
        for (auto i = 0; i < prerequisites.size(); ++i) {
            auto dst = prerequisites[i][0];
            auto src = prerequisites[i][1];
            if (mAdjList.find(src) != mAdjList.end()) {
                mAdjList[src].emplace_back(dst);
            } else {
                std::vector<int> lst{dst};
                mAdjList[src] = lst;
            }
        }

        for (auto i = 0; i < numCourses; ++i) {
            if (mColor[i] == WHITE) {
                dfs(i);
            }
        }

        std::vector<int> order;
        if (mIsPossible) {
            order = std::vector<int>(numCourses);
            for (auto i = 0; i < numCourses; ++i) {
                order[i] = mTopologicalOrder[numCourses - i - 1];
            }
        }
        return order;
    }

private:
    enum {
        WHITE,
        GRAY,
        BLACK,
    };

    bool mIsPossible;
    std::unordered_map<int, int> mColor;
    std::unordered_map<int, std::vector<int>> mAdjList;
    std::vector<int> mTopologicalOrder;

    void init(int n) {
        mIsPossible = true;
        mAdjList.clear();
        mTopologicalOrder.clear();
        for (auto i = 0; i < n; ++i) {
            mColor[i] = WHITE;
        }
    }

    void dfs(int node) {
        if (!mIsPossible) {
            return;
        }

        mColor[node] = GRAY;
        if (mAdjList.count(node) != 0) {
            for (auto neighbor : mAdjList[node]) {
                if (mColor[neighbor] == WHITE) {
                    dfs(neighbor);
                } else if (mColor[neighbor] == GRAY) {
                    mIsPossible = false;
                }
            }
        }

        mColor[node] = BLACK;
        mTopologicalOrder.emplace_back(node);
    }
};
#endif

struct Input {
    using T = std::vector<std::vector<int>>;
    int numCourses;
    T prerequisites;

    Input(int n, T p) : numCourses(n), prerequisites(p) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{2, {{1, 0}}}, {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}}};

    auto print_v = [](const std::vector<int> &order) {
        std::cout << "[";
        for (const auto &o : order) {
            std::cout << o << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &input : inputs) {
        TestCount();
        print_v(sln.findOrder(input.numCourses, input.prerequisites));
    }
}