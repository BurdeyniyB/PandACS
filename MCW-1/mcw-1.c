#include <stdio.h>
#include <stdlib.h>

void printMatrix(int matrix[3][3]);
void printInverseMatrix(float inverse[3][3]);
int determinant(int matrix[3][3]);
void inverse(int matrix[3][3], float inverse[3][3]);
void checkInverse(int matrix[3][3], float inverse[3][3]);

int main() {
    int matrix[3][3];
    float inverseMatrix[3][3];
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл input.txt\n");
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);

    printf("Зчитана матриця з файлу input.txt:\n");
    printMatrix(matrix);

    inverse(matrix, inverseMatrix);

    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Не вдалося відкрити файл output.txt для запису\n");
        return 1;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fprintf(file, "%.2f ", inverseMatrix[i][j]); 
        }
        fprintf(file, "\n");
    }
    printf("Обернена матриця:\n");
    printInverseMatrix(inverseMatrix);
    fclose(file);

    checkInverse(matrix, inverseMatrix);

    return 0;
}

void printMatrix(int matrix[3][3]) {

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d ", matrix[i][j]); 
        }
        printf("\n");
    }
    printf("\n");
}

void printInverseMatrix(float inverse[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%.2f ", inverse[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int determinant(int matrix[3][3]) {
    int det = 0;
    
    det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
        - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
        + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det;
}

void inverse(int matrix[3][3], float inverse[3][3]) {
    int det = determinant(matrix);
    if (det == 0) { 
        printf("Неможливо знайти обернену матрицю, оскільки детермінант дорівнює 0\n");
        return;
    }

    float augmentedMatrix[3][6];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            augmentedMatrix[i][j] = (float)matrix[i][j];
            if (i == j) {
                augmentedMatrix[i][j + 3] = 1.0f; 
            } else {
                augmentedMatrix[i][j + 3] = 0.0f;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        float pivot = augmentedMatrix[i][i];
        if (pivot == 0) {
            printf("Матриця сингулярна, оберненої матриці не існує\n");
            return;
        }
        for (int j = 0; j < 6; ++j) {
            augmentedMatrix[i][j] /= pivot;
        }

        for (int k = 0; k < 3; ++k) {
            if (k != i) {
                float factor = augmentedMatrix[k][i];
                for (int j = 0; j < 6; ++j) {
                    augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                }
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            inverse[i][j] = augmentedMatrix[i][j + 3];
        }
    }
}

void checkInverse(int matrix[3][3], float inverse[3][3]) {
    float result[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result[i][j] += matrix[i][k] * inverse[k][j];
            }
        }
    }

    printf("Добуток вихідної матриці на обернену:\n");
    printInverseMatrix(result);
}