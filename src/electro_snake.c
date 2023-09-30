#include <stdio.h>
#include <stdlib.h>

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int* arr, int M, int N, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int* arr, int M, int N, int **result_matrix);

int** matrix_allocate(int M, int N);

int input(int **matrix, int M, int N);
void output(int **matrix, int M, int N);

void copy(int** matrix, int M, int N, int* arr);

void bubble_sort(int* arr, int N);
void swap(int* a, int* b);

int main()
{
    int M, N;
    if ((scanf("%d %d", &M, &N) == 2) && (getc(stdin) == '\n') && (M > 0) && (N > 0)) { 
        int** matrix = matrix_allocate(M, N);

        if (input(matrix, M, N) == 1) {

            int* arr = malloc(M * N * sizeof(int));
            copy(matrix, M, N, arr);
            bubble_sort(arr, M * N);

            int** result = matrix_allocate(M, N);
            sort_vertical(arr, M, N, result);
            output(result, M, N);

            printf("\n\n");
    
            sort_horizontal(arr, M, N, result);
            output(result, M, N);

            free(result);
        }

        free(matrix);
    } else printf("n/a");

    return 0;
}

int** matrix_allocate(int M, int N) {
    int** matrix = malloc((M + M * N) * sizeof(int));
    int* start = (int*) (matrix + M);
    for (int i = 0; i < M; i++) 
        matrix[i] = start + i * N; 

    return matrix;
}

int input(int** matrix, int M, int N) {
    int flag = 1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                flag = 0;
                break;
            }
        }
    }
    if (getc(stdin) != '\n') flag = 0;

    return flag;
}

void output(int** matrix, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) 
            (j != N - 1) ? printf("%d ", matrix[i][j]) : printf("%d", matrix[i][j]);
        if (i != M - 1) printf("\n");
    }
}

void copy(int** matrix, int M, int N, int* arr) {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            arr[i*N+j] = matrix[i][j]; 
}

void bubble_sort(int* arr, int N) {
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N - i - 1; ++j) 
            if (arr[j] > arr[j+1]) 
                swap(&arr[j], &arr[j+1]);
}

void swap(int* a, int* b) {
    int var = *a;
    *a = *b;
    *b = var;
}

void sort_vertical(int* arr, int M, int N, int **result_matrix) {
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < M; ++i) {
            if (j % 2 == 0)
                result_matrix[i][j] = arr[j*M+i];
            else 
                result_matrix[M-1-i][j] = arr[j*M+i];
        }
    }
}

void sort_horizontal(int* arr, int M, int N, int **result_matrix) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i % 2 == 0) 
                result_matrix[i][j] = arr[i*N+j];
            else 
                result_matrix[i][N-1-j] = arr[i*N+j];
        }
    }
}