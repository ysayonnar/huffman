#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
  int value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *newTreeNode(int value);
void insertTree(TreeNode **tree, int value);
void freeTree(TreeNode *tree);

#endif
