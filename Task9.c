#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;
int size = 0;

Node *createNode(int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void printList() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = head;
    while (temp != NULL) {
        printf("[%d]", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void insertAtBeginning(int data) {
    Node *newNode = createNode(data);

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    size++;
}

void insertAtEnd(int data) {
    Node *newNode = createNode(data);

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

void insertAtPosition(int data, int position) {
    if (position < 0) {
        return;
    }

    if (position == 0) {
        insertAtBeginning(data);
        return;
    }

    if (position >= size) {
        insertAtEnd(data);
        return;
    }

    Node *newNode = createNode(data);

    if (position < size / 2) {
        Node *temp = head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
    } else {
        Node *temp = tail;
        for (int i = size - 1; i > position; i--) {
            temp = temp->prev;
        }

        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        newNode->next = temp;
    }

    size++;
}

void deleteAtBeginning() {
    if (head == NULL) {
        return;
    }

    Node *temp = head;
    if (head == tail) {
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
    size--;
}

void deleteAtEnd() {
    if (head == NULL) {
        return;
    }

    Node *temp = tail;
    if (head == tail) {
        head = NULL;
        tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }

    free(temp);
    size--;
}

void deleteAtPosition(int position) {
    if (position < 0 || position >= size) {
        return;
    }

    if (position == 0) {
        deleteAtBeginning();
        return;
    }

    if (position == size - 1) {
        deleteAtEnd();
        return;
    }

    if (position < size / 2) {
        Node *temp = head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }

        Node *temp2 = temp->next;
        temp->next = temp2->next;
        temp2->next->prev = temp;
        free(temp2);
    } else {
        Node *temp = tail;
        for (int i = size - 1; i > position + 1; i--) {
            temp = temp->prev;
        }

        Node *temp2 = temp->prev;
        temp->prev = temp2->prev;
        temp2->prev->next = temp;
        free(temp2);
    }

    size--;
}

int peekFirst() {
    if (head == NULL) {
        return -1;
    }

    return head->data;
}

int peekLast() {
    if (head == NULL) {
        return -1;
    }

    return tail->data;
}

int popFirst() {
    if (head == NULL) {
        return -1;
    }

    int data = head->data;
    deleteAtBeginning();
    return data;
}

int popLast() {
    if (head == NULL) {
        return -1;
    }

    int data = tail->data;
    deleteAtEnd();
    return data;
}

void clean() {
    while (head != NULL) {
        deleteAtBeginning();
    }

    size = 0;
}

int main() {
    return 0;
}