#include "tree.h"
#include "stdlib.h"

TreeNode *newTreeNode(int value) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

void insertTree(TreeNode **tree, int value) {
  if (*tree == NULL) {
    *tree = newTreeNode(value);
    return;
  }

  TreeNode *currentNode = *tree;
  while (currentNode != NULL) {
    if (value == currentNode->value) {
      return;
    } else if (value < currentNode->value) {
      if (currentNode->left == NULL) {
        currentNode->left = newTreeNode(value);
        break;
      }
      currentNode = currentNode->left;
    } else if (value > currentNode->value) {
      if (currentNode->right == NULL) {
        currentNode->right = newTreeNode(value);
        break;
      }
      currentNode = currentNode->right;
    }
  }
}

void freeTree(TreeNode *tree) {
  if (tree == NULL) {
    return;
  }

  freeTree(tree->left);
  freeTree(tree->right);

  free(tree);
  tree = NULL;
}
