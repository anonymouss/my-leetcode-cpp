/**
 * Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the
 * root node of a BST.
 * Calling next() will return the next smallest number in the BST.
 * Example:
 *
 * << IMAGE >>
 *
 * BSTIterator iterator = new BSTIterator(root);
 * iterator.next();    // return 3
 * iterator.next();    // return 7
 * iterator.hasNext(); // return true
 * iterator.next();    // return 9
 * iterator.hasNext(); // return true
 * iterator.next();    // return 15
 * iterator.hasNext(); // return true
 * iterator.next();    // return 20
 * iterator.hasNext(); // return false
 *
 * Note:
 * next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height
 * of the tree. You may assume that next() call will always be valid, that is, there will be at
 * least a next smallest number in the BST when next() is called.
 */

#include "MyBinaryTreeUtil.h"
#include "MyMisc.h"

#include <iostream>
#include <stack>
#include <vector>

constexpr int null = -1;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode* root) : curNode(root) {}

    /** @return the next smallest number */
    int next() {
        int val = -1;
        while (curNode || !visited.empty()) {
            while (curNode) {
                visited.push(curNode);
                curNode = curNode->left;
            }
            curNode = visited.top();
            val = curNode->val;  // curNode won't be null
            visited.pop();
            curNode = curNode->right;
            break;
        }
        return val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() { return curNode != nullptr || !visited.empty(); }

private:
    TreeNode* curNode;
    std::stack<TreeNode*> visited;
};

/**f
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

#define DISP(val) \
    { std::cout << (val) << std::endl; }

int main() {
    std::vector<int> nodes{7, 3, 15, null, null, 9, 20};

    TestCount(IOFormat::BOOL);
    BSTIterator bsti{myGenerateTreeFromLeetCodeInput(nodes)};
    DISP(bsti.next());     // 3
    DISP(bsti.next())      // 7
    DISP(bsti.hasNext());  // true
    DISP(bsti.next());     // 9
    DISP(bsti.hasNext());  // true
    DISP(bsti.next());     // 15
    DISP(bsti.hasNext());  // true
    DISP(bsti.next());     // 20
    DISP(bsti.hasNext());  // false

    // myDispTreeInorder(myGenerateTreeFromLeetCodeInput(nodes));
}