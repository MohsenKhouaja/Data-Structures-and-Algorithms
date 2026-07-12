// https://leetcode.com/problems/count-good-nodes-in-binary-tree/#pragma GCC optimize("O3,unroll-loops")
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
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        
    }
};

class Solution
{
public:
    int score = 0;
    int goodNodes(TreeNode *root)
    {
        traverse(root, root->val);
        return score;
    }
    void traverse(TreeNode *root, int mx)
    {
        if (root != nullptr)
        {
            if (root->val >= mx)
            {
                score++;
                mx = root->val;
            }
            traverse(root->left, mx);
            traverse(root->right, mx);
        }
    }
};