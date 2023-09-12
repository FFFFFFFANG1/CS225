//DFS
//pre-order traversal of tree
void preOrder(Node *root)
{
    if (root == NULL) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

//in-order traversal of tree
void inOrder(Node *root)
{
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

//post-order traversal of tree
void postOrder(Node *root)
{
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

//BFS
//level-order traversal of tree 
void levelOrder(Node *root) 
{
    if (root == NULL) return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()){
        Node *temp = q.dequeue();
        if (t != NULL){
            cout << temp->data << " ";
            q.enqueue(temp->left);
            q.enqueue(temp->right);
        }
    }
}