#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FULL_SIZE 200

int currentSize = FULL_SIZE;

void* my_malloc(size_t size) {
    if (size <= currentSize) {
        currentSize -= size;
        return &currentSize + currentSize; 
    }
    else {
        return malloc(size); 
    }
}

void my_free(void* ptr) {
    if (ptr < &currentSize || ptr >= (&currentSize + FULL_SIZE)) {
        free(ptr);
    }
}

void* my_realloc(void* ptr, size_t newSize) {
    if (ptr >= &currentSize && ptr < (&currentSize + FULL_SIZE)) {
        void* newPtr = malloc(newSize);
        if (newPtr == NULL) return NULL;
        memcpy(newPtr, ptr, newSize);
        return newPtr;
    }
    else {
        return realloc(ptr, newSize);
    }
}

struct Queue {
    int number;
    struct Queue* next;
};

void push(struct Queue** front, struct Queue** rear, int value) {
    struct Queue* newNode = (struct Queue*) my_malloc(sizeof(struct Queue));
    newNode->number = value;
    newNode->next = NULL;
    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

void pop(struct Queue** front, struct Queue** rear) {
    if (*front == NULL) {
        return;
    }
    struct Queue* temp = *front;
    *front = (*front)->next;
    my_free(temp);
    if (*front == NULL) {
        *rear = NULL;
    }
}

void printQueue(struct Queue* front) {
    while (front != NULL) {
        printf("%d ", front->number);
        front = front->next;
    }
    printf("\n");
}

void clearQueue(struct Queue** front, struct Queue** rear) {
    while (*front != NULL) {
        struct Queue* temp = *front;
        *front = (*front)->next;
        my_free(temp);
    }
    *rear = NULL;
}

int main() {
    struct Queue* front = NULL;
    struct Queue* rear = NULL;

    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        push(&front, &rear, rand() % 101);
    }

    printf("Черга перед видаленням непарних чисел: ");
    printQueue(front);

    struct Queue* current = front;
    struct Queue* previous = NULL;
    while (current != NULL) {
        if (current->number % 2 != 0) {
            if (current == front) {
                pop(&front, &rear);
                current = front;
            } else {
                previous->next = current->next;
                my_free(current);
                current = previous->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }

    printf("Черга після видалення непарних чисел: ");
    printQueue(front);

    clearQueue(&front, &rear);

    return 0;
}
