#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define M 5
#define N 5
#define FULL_SIZE 200

int currentSize = FULL_SIZE;

void* my_malloc(size_t size);
void my_free(void* ptr);
void* my_realloc(void* ptr, size_t newSize);
void fill_matrix(int matrix[M][N]);
void print_matrix(int matrix[M][N]);
void write_matrix_to_file(int matrix[M][N], const char* filename);

int main() {
    void *ptr = my_malloc(M * sizeof(int[N]));
    int (*matrix)[N] = (int (*)[N])ptr;

    fill_matrix(matrix);

    printf("Матриця %dx%d:\n", M, N);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    int main_diag_sum = 0, side_diag_sum = 0;
    for (int i = 0; i < M; ++i) {
        main_diag_sum += matrix[i][i];
        side_diag_sum += matrix[i][N - 1 - i];
    }
    printf("Сума елементів головної діагоналі: %d\n", main_diag_sum);
    printf("Сума елементів побічної діагоналі: %d\n", side_diag_sum);

    write_matrix_to_file(matrix, "matrix.txt");

    my_free(ptr);

    return 0;
}

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

void fill_matrix(int matrix[M][N]) {
    srand(time(NULL));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void print_matrix(int matrix[M][N]) {
    printf("Матриця %dx%d:\n", M, N);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void write_matrix_to_file(int matrix[M][N], const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "Матриця %dx%d:\n", M, N);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                fprintf(file, "%d\t", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Матрицю записано у файл '%s'\n", filename);
    } else {
        printf("Помилка при відкритті файлу для запису\n");
    }
}