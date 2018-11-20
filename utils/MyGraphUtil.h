#ifndef __UTILS_MY_GRAPH_UTIL__
#define __UTILS_MY_GRAPH_UTIL__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::pair;
using std::queue;
using std::unordered_set;

/**************************************************************************************************/
/*                                      Definition                                                */
/**************************************************************************************************/
// defined by leetcode
// undirected graph
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

/**************************************************************************************************/
/*                                        Utils                                                   */
/**************************************************************************************************/
template <typename T = UndirectedGraphNode>
struct MyHash {
    std::size_t operator()(const T *t) const {
        return std::hash<int>(t->label);
    }
};

template <typename T = UndirectedGraphNode>
struct MyEqualTo {
    bool operator()(const T *lhs, const T *rhs) const {
        return lhs->label == rhs->label;
    }
};

#define INT(c) (c - '0')

/**
 * @brief: generate the undirected graph according to leetcode defined serialized input
 * 
 * @param   nodes   serialized graph nodes in leetcode format
 * @return          root node of the generated graph
 */
template <typename T = UndirectedGraphNode>
T *myGenerateUndirectedGraphFromLeetCodeInput(vector<char> &nodes) {
    if (nodes.empty() || (nodes.size() == 1 && nodes[0] == '#')) return nullptr;
    auto *root = new T(INT(nodes[0]));
    auto *cur = root;
    unordered_map<int, T *> nodesMap{{INT(nodes[0]), root}};
    for (int i = 1, n = nodes.size(); i < n; ++i) {
        auto c = nodes[i];
        if (c == '#') {
            if (++i >= n) break;
            c = nodes[i]; // update
            auto itr = nodesMap.find(INT(c));
            if (itr != nodesMap.end()) {
                cur = itr->second;
            } else {
                auto *node = new T(INT(c));
                cur = node;
                nodesMap.emplace(pair<int, T *>{INT(c), node});
            }
        } else {
            auto itr = nodesMap.find(INT(c));
            if (itr != nodesMap.end()) {
                cur->neighbors.emplace_back(itr->second);
            } else {
                auto *node = new T(INT(c));
                cur->neighbors.emplace_back(node);
                nodesMap.emplace(pair<int, T *>{INT(c), node});
            }
        }
    }
    return root;
}

/**
 * @brief: display serialized graph nodes in leetcode format
 * 
 * '#' is the separator. in each segment, the first val is current node, remanings are it's neighbors
 * 
 * @param   root    root node of one graph
 */
template <typename T = UndirectedGraphNode>
void myDispUndirectedGraphNeighbors(T *root) {
    if (!root) return;
    queue<T *> nodesQueue;
    unordered_set<char> recorder;
    nodesQueue.emplace(root);
    recorder.emplace(root->label);
    while (!nodesQueue.empty()) {
        auto *node = nodesQueue.front();
        nodesQueue.pop();
        std::cout << node->label << ", ";
        for (auto *neighbor : node->neighbors) {
            std::cout << neighbor->label << ", ";
            if (!recorder.count(neighbor->label)) {
                nodesQueue.emplace(neighbor);
                recorder.emplace(neighbor->label);
            }
        }
        if (!nodesQueue.empty())
            std::cout << "#, ";
    }
    std::cout << std::endl;
}

#endif // __UTILS_MY_GRAPH_UTIL__