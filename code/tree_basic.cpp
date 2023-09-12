//check if tree is full binary tree
bool isFullBinaryTree(Node *root)
{
    if (root == NULL)
        return true;
    if (root->left == NULL && root->right == NULL)
        return true;
    if ((root->left) && (root->right))
        return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));
    return false;
}

//check if tree is complete binary tree
bool isCompleteBinaryTree(Node *root, int index, int number_nodes) //index start at root from 0
{
    if (root == NULL)
        return true;
    if (index >= number_nodes)
        return false;
    return (isCompleteBinaryTree(root->left, 2 * index + 1, number_nodes) && isCompleteBinaryTree(root->right, 2 * index + 2, number_nodes));
}

//check if tree is perfect binary tree
bool isPerfectBinaryTree(Node *root, int depth, int level = 0) //level start at root from 0
{
    if (root == NULL)
        return true;
    if (root->left == NULL && root->right == NULL)
        return (depth == level + 1);
    if (root->left == NULL || root->right == NULL)
        return false;
    return (isPerfectBinaryTree(root->left, depth, level + 1) && isPerfectBinaryTree(root->right, depth, level + 1));
}