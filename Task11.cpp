#include <iostream>
#include <vector>

#define COUNT 5
#define SIZE 10

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int data) {
    Node *node = new Node;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void add(Node **head, int data) {
    Node *newNode = createNode(data);

    if (!*head) {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    while (temp) {
        if (data < temp->data) {
            if (temp->left == nullptr) {
                temp->left = newNode;
                return;
            }

            temp = temp->left;
        } else {
            if (temp->right == nullptr) {
                temp->right = newNode;
                return;
            }

            temp = temp->right;
        }
    }
}

void printTreeUtility(struct Node *root, int space) {
    if (!root) {
        return;
    }

    space += COUNT;

    printTreeUtility(root->right, space);

    printf("\n");

    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }

    printf("%d\n", root->data);

    printTreeUtility(root->left, space);
}

void printTree(struct Node *root) {
    printTreeUtility(root, 0);
}

bool hasPath(Node *root, std::vector<int> &arr, int x) {
    if (!root) {
        return false;
    }

    arr.push_back(root->data);

    if (root->data == x) {
        return true;
    }

    if (hasPath(root->left, arr, x) || hasPath(root->right, arr, x)) {
        return true;
    }

    arr.pop_back();

    return false;
}

std::vector<int> findPath(Node *root, int x) {
    std::vector<int> arr;
    hasPath(root, arr, x);
    return arr;
}

int main() {
    srand(time(nullptr) / 2);

    int *arr = new int[SIZE];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }

    Node *root = nullptr;

    for (int i = 0; i < SIZE; i++) {
        add(&root, arr[i]);
    }

    printTree(root);

    for (int i = 0; i < SIZE; i++) {
        std::vector<int> path = findPath(root, arr[i]);

        for (int j: path) {
            std::cout << "[" << j << "]";
        }

        std::cout << std::endl;
    }

    delete[] arr;

    return 0;
}