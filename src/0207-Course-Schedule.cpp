/**
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course
 * 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, is it possible for you to
 * finish all courses?
 *
 * Example 1:
 * Input: 2, [[1,0]] 
 * Output: true
 * Explanation: There are a total of 2 courses to take. 
 *              To take course 1 you should have finished course 0. So it is possible.
 *
 * Example 2:
 * Input: 2, [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take. 
 *              To take course 1 you should have finished course 0, and to take course 0 you should
 *              also have finished course 1. So it is impossible.
 *
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read
 * more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input prerequisites.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <queue>

#define IN_DEGREE 0
#define DFS 1

#define COMPILE_VERSION DFS

#if (COMPILE_VERSION == IN_DEGREE)
class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        std::vector<int> inDegrees(numCourses);
        for(auto &prerequisite : prerequisites) {
            inDegrees[prerequisite[0]]++;
        }
        std::queue<int> queue;
        for (auto i = 0; i < numCourses; ++i) {
            if (inDegrees[i] == 0) {
                queue.emplace(i);
            }
        }
        while(!queue.empty()) {
            auto pre = queue.front();
            queue.pop();
            --numCourses;
            for (auto &prerequisite : prerequisites) {
                if (prerequisite[1] != pre) {
                    continue;
                }
                if (--inDegrees[prerequisite[0]] == 0) {
                    queue.emplace(prerequisite[0]);
                }
            }
        }
        return numCourses == 0;
    }
};
#elif (COMPILE_VERSION == DFS)
class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
        std::vector<std::vector<int>> adjacency(numCourses, std::vector<int>(numCourses, 0));
        std::vector<int> flags(numCourses, 0);
        for (auto &prerequisite : prerequisites) {
            adjacency[prerequisite[1]][prerequisite[0]] = 1;
        }
        for (auto i = 0; i < numCourses; ++i) {
            if (!dfs(adjacency, flags, i)) {
                return false;
            }
        }
        return true;
    }

private:
    bool dfs(std::vector<std::vector<int>> &adjacency, std::vector<int> &flags, int i) {
        if (flags[i] == 1) {
            return false;
        }
        if (flags[i] == -1) {
            return true;
        }
        flags[i] = 1;
        for (auto j = 0; j < adjacency.size(); ++j) {
            if (adjacency[i][j] == 1 && !dfs(adjacency, flags, j)) {
                return false;
            }
        }
        flags[i] = -1;
        return true;
    }
};
#endif

struct Input {
    int numCourses;
    std::vector<std::vector<int>> prerequisites;
    Input(int n, std::vector<std::vector<int>> p) : numCourses(n), prerequisites(p) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{2, {{1, 0}}}, {2, {{1, 0}, {0, 1}}}};

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.canFinish(input.numCourses, input.prerequisites) << std::endl;
    }
}