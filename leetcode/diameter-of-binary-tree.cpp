// revisit

// https://leetcode.com/problems/diameter-of-binary-tree/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int mx = 0;
    int diameterOfBinaryTree(TreeNode *root)
    {
        // it's the max of the sums of depth of both subtrees
        maxDepth(root);
        return mx;
    }
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        int depth = 1 + max(l, r);
        mx = max(mx, l + r);
        return depth;
    }
};
