#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("| %2d ", arr[i]);
    }
    printf("|\n");
}

int* removeNegativeElements(int* arr, int size, int* newSize) {
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0) {
            arr[j++] = arr[i];
        }
    }
    *newSize = j;
    return arr;
}

void addColumnAndPrint(int** dynamicMatrix) {
    printf("Dynamic Matrix before adding a column:\n");
    for (int i = 0; i < 3; i++) {
        printArray(dynamicMatrix[i], 3);
    }

    for (int i = 0; i < 3; i++) {
        dynamicMatrix[i] = (int*)my_realloc(dynamicMatrix[i], 4 * sizeof(int));
        memmove(dynamicMatrix[i] + 1, dynamicMatrix[i], 3 * sizeof(int));
        dynamicMatrix[i][0] = rand() % 21 - 10; 
    }

    printf("Dynamic Matrix after adding a column:\n");
    for (int i = 0; i < 3; i++) {
        printArray(dynamicMatrix[i], 4);
    }
}

int main() {
    srand(time(NULL));

    int* dynamicArray = (int*)my_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        dynamicArray[i] = rand() % 21 - 10; 
    }

    printf("Dynamic Array before removing negative elements:\n");
    printArray(dynamicArray, 10);

    int newSize;
    dynamicArray = removeNegativeElements(dynamicArray, 10, &newSize);

    printf("Dynamic Array after removing negative elements:\n");
    printArray(dynamicArray, newSize);

    int** dynamicMatrix = (int**)my_malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        dynamicMatrix[i] = (int*)my_malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            dynamicMatrix[i][j] = rand() % 21 - 10; 
        }
    }

    addColumnAndPrint(dynamicMatrix);

    for (int i = 0; i < 3; i++) {
        my_free(dynamicMatrix[i]);
    }
    my_free(dynamicMatrix);
    my_free(dynamicArray);

    return 0;
}
