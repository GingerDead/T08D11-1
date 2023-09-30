#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int input_size(int* M, int* N);
int input(double **matrix, int M, int N);
void output(double det);

double** matrix_allocate(int M, int N);

double det_recursive(double **matrix, int len);
void get_alg_comp(double** matrix, int size, int column, double** new_matrix);

int main() {   
    int M, N;
    if (input_size(&M, &N) == 1) {
        double** matrix = matrix_allocate(M, N);
        if (input(matrix, M, N) == 1) {
            double determinant = det_recursive(matrix, M);
            output(determinant);
        } else printf("n/a");
        free(matrix);
    } else printf("n/a");

    return 0;
}

int input_size(int* M, int* N) {
    int flag = 1;
    if ((scanf("%d %d", M, N) != 2) || (getc(stdin) != '\n') || (*M <= 0) || (*N <= 0) || (*M != *N)) flag = 0;
    return flag;
}

int input(double** matrix, int M, int N) {
    int flag = 1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                flag = 0;
                break;
            }
        }
    }
    if (getc(stdin) != '\n') flag = 0;

    return flag;
}

void output(double det) {
    printf("%.6f", det);
}

double** matrix_allocate(int M, int N) {
    double** matrix = malloc((M + M * N) * sizeof(double));
    double* start = (double*) (matrix + M);
    for (int i = 0; i < M; i++) 
        matrix[i] = start + i * N; 

    return matrix;
}

double det_recursive(double **matrix, int size) {
    double determinant;
    switch (size) {
    
    case 1:
        determinant = matrix[0][0];
        break;

    case 2:
        determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        break;
    
    default:
        double** alg_comp = matrix_allocate(size -1, size -1);
        for (int j = 0; j < size; ++j) {
            get_alg_comp(matrix, size, j, alg_comp);
            determinant += matrix[0][j] * pow(-1, j) * det_recursive(alg_comp, size - 1);
        }
        free(alg_comp);
        break;
    }

    return determinant;
}

void get_alg_comp(double** matrix, int size, int column, double** new_matrix) {
    int k = 0;
    for (int i = 1; i < size; ++i) {
        int l = 0;
        for (int j = 0; j < size; ++j) {
            if (j != column) {
                new_matrix[k][l] = matrix[i][j];
                ++l;
            }
        }
        ++k;
    }
}