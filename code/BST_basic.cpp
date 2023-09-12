//find_ for binary search tree
Node & BST::find_(int key, Node *& root) const
{
    if (root == NULL)
        return NULL;
    if (root->data == key)
        return root;
    if (root->data > key)
        return find_(key, root->left);
    else
        return find_(key, root->right);
}

// insert_ for binary search tree
void BST::insert_(int key, Node *& root)
{
    Node* element = find_(key, root);
    if (element != NULL)
        return;
    element = new Node(key);
}

//remove_ for binary search tree
void BST::remove_(int key, Node *& root)
{
    Node* element = find_(key, root);
    if (element == NULL)
        return;

    //no children case
    if (element->left == NULL && element->right == NULL)
    {
        delete element;
        element = NULL;
    }
    //one child case
    else if (element->left == NULL)
    {
        Node* temp = element;
        element = element->right;
        delete temp;
    }
    else if (element->right == NULL)
    {
        Node* temp = element;
        element = element->left;
        delete temp;
    }
    //two children case, IOP
    else
    {
        Node* temp = element->left;
        while (temp->right != NULL)
            temp = temp->right;
        element->data = temp->data;
        remove_(temp->data, element->left);
    }
}


void isBST(NOde* root, bool & isBST){
    if (root == NULL)
        return;
    if (root->left != NULL && root->left->data > root->data)
        isBST = false;
        return;
    if (root->right != NULL && root->right->data < root->data)
        isBST = false;
        return;
    isBST(root->left, isBST);
    isBST(root->right, isBST);
}
