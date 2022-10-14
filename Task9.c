#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;
int size = 0;

void printList() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    while (temp != NULL) {
        printf("[%d]", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void insertAtBeginning(int data) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

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
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

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
    if (position <= 1) {
        insertAtBeginning(data);
        return;
    }

    if (position > size) {
        insertAtEnd(data);
        return;
    }

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    struct Node *temp = head;
    int i = 1;

    while (i < position - 1) {
        temp = temp->next;
        i++;
    }

    newNode->next = temp->next;
    temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteAtBeginning() {
    if (head == NULL) {
        return;
    }

    struct Node *temp = head;
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

    struct Node *temp = tail;
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
    if (position <= 1) {
        deleteAtBeginning();
        return;
    }

    if (position >= size) {
        deleteAtEnd();
        return;
    }

    struct Node *temp = head;
    int i = 1;

    while (i < position - 1) {
        temp = temp->next;
        i++;
    }

    struct Node *temp2 = temp->next;
    temp->next = temp2->next;
    temp2->next->prev = temp;
    free(temp2);
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
}

int readInt() {
    int n;
    scanf_s("%d", &n);
    return n;
}

int main() {
    for (int i = 0; i < 5; i++) {
        printf("Inserting %d at beginning: ", i);
        insertAtBeginning(i);
        printList();
    }

    for (int i = 0; i < 5; i++) {
        printf("Inserting %d at end: ", i + 5);
        insertAtEnd(i + 5);
        printList();
    }

    for (int i = 0; i < 5; i++) {
        printf("Inserting %d at position %d: ", i + 10, i * 2);
        insertAtPosition(i + 10, i * 2);
        printList();
    }

    for (int i = 0; i < 5; i++) {
        printf("Deleting at beginning: ");
        deleteAtBeginning();
        printList();
    }

    for (int i = 0; i < 5; i++) {
        printf("Deleting at end: ");
        deleteAtEnd();
        printList();
    }

    printf("Deleting at position 3: ");
    deleteAtPosition(3);
    printList();

    printf("Deleting at position 1: ");
    deleteAtPosition(1);
    printList();

    printf("Deleting at position 3: ");
    deleteAtPosition(3);
    printList();

    printf("Peeking first %d: ", peekFirst());
    printList();

    printf("Peeking last %d: ", peekLast());
    printList();

    printf("Popping first %d: ", popFirst());
    printList();

    printf("Popping last %d: ", popLast());
    printList();

    for (int i = 0; i < 5; i++) {
        printf("Inserting %d at beginning: ", i);
        insertAtBeginning(i);
        printList();
    }

    printf("Cleaning list: ");
    clean();
    printList();

    while (1) {
        printf("1. Insert at beginning\n2. Insert at end\n3. Insert at position\n4. Delete at beginning\n5. Delete at end\n"
               "6. Delete at position\n7. Peek first\n8. Peek last\n9. Pop first\n10. Pop last\n11. Print list\n12. Clean\n13. Exit\n");

        printf("Enter your choice:");

        switch (readInt()) {
            case 1:
                printf("Enter data:");
                insertAtBeginning(readInt());
                break;
            case 2:
                printf("Enter data:");
                insertAtEnd(readInt());
                break;
            case 3:
                printf("Enter data:");
                int data = readInt();
                printf("Enter position:");
                int position = readInt();
                insertAtPosition(data, position);
                break;
            case 4:
                deleteAtBeginning();
                break;
            case 5:
                deleteAtEnd();
                break;
            case 6:
                printf("Enter position:");
                deleteAtPosition(readInt());
                break;
            case 7:
                printf("First element: %d", peekFirst());
                break;
            case 8:
                printf("Last element: %d", peekLast());
                break;
            case 9:
                printf("Popped element: %d", popFirst());
                break;
            case 10:
                printf("Popped element: %d", popLast());
                break;
            case 11:
                printList();
                break;
            case 12:
                clean();
                break;
            case 13:
                exit(0);
            default:
                printf("Invalid choice");
        }
    }
}