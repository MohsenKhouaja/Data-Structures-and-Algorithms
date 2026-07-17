// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
// re
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.size() == 0)
            return nullptr;
        int rootVal = preorder[0];
        pair<vector<int>, vector<int>> leftPair = left(rootVal, preorder, inorder);
        pair<vector<int>, vector<int>> rightPair = right(rootVal, preorder, inorder);
        return new TreeNode(rootVal, buildTree(leftPair.first, leftPair.second), buildTree(rightPair.first, rightPair.second));
    }

    pair<vector<int>, vector<int>> left(int nodeVal, vector<int> &preorder, vector<int> &inorder)
    {
        int inPos = find(inorder.begin(), inorder.end(), nodeVal) - inorder.begin();
        int leftSize = inPos;

        vector<int> leftPre(preorder.begin() + 1, preorder.begin() + 1 + leftSize);
        vector<int> leftIn(inorder.begin(), inorder.begin() + inPos);
        // You can return both or handle them as needed
        return {leftPre, leftIn};
    }
    pair<vector<int>, vector<int>> right(int nodeVal, vector<int> &preorder, vector<int> &inorder)
    {
        int inPos = find(inorder.begin(), inorder.end(), nodeVal) - inorder.begin();
        int leftSize = inPos;

        vector<int> rightPre(preorder.begin() + 1 + leftSize, preorder.end());
        vector<int> rightIn(inorder.begin() + inPos + 1, inorder.end());
        // You can return both or handle them as needed
        return {rightPre, rightIn};
    }
};
