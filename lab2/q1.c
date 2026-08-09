#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

/* Create a new node */
struct Node* createNode(int key)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* 1. INSERT */
struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

/* 2. SEARCH */
struct Node* search(struct Node* root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

/* 3. MINIMUM */
struct Node* minimum(struct Node* root)
{
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

/* 4. MAXIMUM */
struct Node* maximum(struct Node* root)
{
    if (root == NULL)
        return NULL;

    while (root->right != NULL)
        root = root->right;

    return root;
}

/* 5. DELETE */
struct Node* deleteNode(struct Node* root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // No left child
        if (root->left == NULL)
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        // No right child
        if (root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        struct Node* temp = minimum(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

/* 6. PREDECESSOR */
struct Node* predecessor(struct Node* root, int key)
{
    struct Node* pred = NULL;

    while (root != NULL)
    {
        if (key > root->key)
        {
            pred = root;
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }

    return pred;
}

/* 7. SUCCESSOR */
struct Node* successor(struct Node* root, int key)
{
    struct Node* succ = NULL;

    while (root != NULL)
    {
        if (key < root->key)
        {
            succ = root;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return succ;
}

/* Inorder traversal */
void inorder(struct Node* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

/* MAIN */
int main()
{
    struct Node* root = NULL;

    /* Insert */
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Dictionary elements: ");
    inorder(root);

    /* Search */
    int key = 40;

    struct Node* s = search(root, key);

    if (s != NULL)
        printf("\nSearch %d: Found", key);
    else
        printf("\nSearch %d: Not Found", key);

    /* Minimum */
    struct Node* min = minimum(root);
    printf("\nMinimum: %d", min->key);

    /* Maximum */
    struct Node* max = maximum(root);
    printf("\nMaximum: %d", max->key);

    /* Predecessor */
    struct Node* pred = predecessor(root, key);

    if (pred != NULL)
        printf("\nPredecessor of %d: %d", key, pred->key);
    else
        printf("\nNo predecessor");

    /* Successor */
    struct Node* succ = successor(root, key);

    if (succ != NULL)
        printf("\nSuccessor of %d: %d", key, succ->key);
    else
        printf("\nNo successor");

    /* Delete */
    root = deleteNode(root, 30);

    printf("\nAfter deleting 30: ");
    inorder(root);

    return 0;
}