#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int ascendingCompare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

Node *createNode(int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    return newNode;
}

void push(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

int pop(Node **head) {
    Node *temp = *head;
    int data = temp->data;

    *head = temp->next;
    free(temp);

    return data;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("[%d]", head->data);
        head = head->next;
    }

    printf("\n");
}

void clear(Node **head) {
    Node *temp = *head;

    while (temp != NULL) {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
}

Node* merge(Node *stack1, Node *stack2) {
    Node *stack3 = NULL;

    while (stack1 != NULL && stack2 != NULL) {
        if (stack1->data == stack2->data) {
            push(&stack3, pop(&stack1));
            push(&stack3, pop(&stack2));
        } else {
            push(&stack3, stack1->data > stack2->data ? pop(&stack1) : pop(&stack2));
        }
    }

    while (stack1 != NULL) {
        push(&stack3, pop(&stack1));
    }

    while (stack2 != NULL) {
        push(&stack3, pop(&stack2));
    }

    return stack3;
}

int main() {
    srand(time(NULL) / 2);

    int m = random(0, MAX);
    int n = random(0, MAX);

    int *array1 = malloc(sizeof(int) * m);
    int *array2 = malloc(sizeof(int) * n);

    for (int i = 0; i < m; i++) {
        array1[i] = rand() % 100 + 1;
    }

    for (int i = 0; i < n; i++) {
        array2[i] = rand() % 100 + 1;
    }

    qsort(array1, m, sizeof(int), ascendingCompare);
    qsort(array2, n, sizeof(int), ascendingCompare);

    Node *stack1 = NULL;
    Node *stack2 = NULL;

    for (int i = 0; i < m; i++) {
        push(&stack1, array1[i]);
    }

    for (int i = 0; i < n; i++) {
        push(&stack2, array2[i]);
    }

    printList(stack1);
    printList(stack2);

    Node *stack3 = merge(stack1, stack2);

    printList(stack3);

    clear(&stack3);
    free(array1);
    free(array2);
}