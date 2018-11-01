# Notes

## [Morris Traversal](https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html) (O(1) space complexity)

### inorder traversal

0. start from `root` node (`curNode = root`)
1. if `curNode->left == nullptr`, then echo `curNode->val` and let `curNode = curNode->right`
2. else if `curNode->left != nullptr`, find it's `preNode` in inorder traversal in it's left sub-tree
- a. if `preNode->right == nullptr`, then let `preNode->right = curNode` and `curNode = curNode->left`
- b. else if `preNode->right == curNode`, then  `preNode->right = nullptr`(restore), echo `curNode->val` and let `curNode = curNode->right`
3. repeat 1. and 2. until `curNode == nullptr`