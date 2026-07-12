// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
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
    int counter = 0;
    int res = -1;
    int kthSmallest(TreeNode *root, int k)
    {
        traverse(root, k);
        printTree(root);
        return res;
    }
    void traverse(TreeNode *root, int k)
    {
        if (root == nullptr || res != -1)
            return;
        traverse(root->right, k);
        counter++;
        if (counter == k)
        {
            res = root->val;
            return;
        }
        traverse(root->left, k);
    }
    void printTree(TreeNode *root)
    {
        if (root == nullptr)
            return;
        printTree(root->left);
        cout << root->val << " ";
        printTree(root->right);
    }
};
