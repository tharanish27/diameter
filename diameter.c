
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Structure to store the height and diameter of a subtree
typedef struct Result {
    int height;
    int diameter;
} Result;

// Function to calculate the height and diameter of the binary tree
Result diameterHelper(TreeNode* root) {
    Result result = {0, 0}; // Initialize height and diameter
    
    if (root == NULL) {
        result.height = 0;
        result.diameter = 0;
        return result;
    }

    // Get the result of left and right subtrees
    Result leftResult = diameterHelper(root->left);
    Result rightResult = diameterHelper(root->right);

    // Calculate the height of the current node
    result.height = (leftResult.height > rightResult.height ? leftResult.height : rightResult.height) + 1;

    // Calculate the diameter of the current node
    int leftDiameter = leftResult.diameter;
    int rightDiameter = rightResult.diameter;
    int diameterThroughRoot = leftResult.height + rightResult.height + 1;
    result.diameter = (leftDiameter > rightDiameter ? leftDiameter : rightDiameter);
    result.diameter = (result.diameter > diameterThroughRoot ? result.diameter : diameterThroughRoot);

    return result;
}

// Function to calculate the diameter of the binary tree
int calculateDiameter(TreeNode* root) {
    Result result = diameterHelper(root);
    return result.diameter;
}

// Function to free the memory of the binary tree
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main function to demonstrate the diameter calculation
int main() {
    // Create a simple binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Calculate and print the diameter of the tree
    int diameter = calculateDiameter(root);
    printf("Diameter of the binary tree: %d\n", diameter);

    // Free allocated memory
    freeTree(root);

    return 0;
}
