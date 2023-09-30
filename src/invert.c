#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int input_size(int* M, int* N);
int input(double** matrix, int M, int N);
void output(double** matrix, int M, int N);

double** matrix_allocate(int M, int N);

int invert(double** matrix, int M, int N);
double** trans(double** matrix, int M, int N);
double det_recursive(double** matrix, int size);
void get_alg_comp(double** matrix, int size, int row, int column, double** new_matrix);


int main() {
    int M, N;
    if (input_size(&M, &N) == 1) {
        double** matrix = matrix_allocate(M, N);
        if (input(matrix, M, N) == 1) {
            if (invert(matrix, M, N)) 
                output(matrix, M, N);
            else printf("n/a");
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

void output(double** matrix, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) 
            (j != N - 1) ? printf("%.6f ", matrix[i][j]) : printf("%.6f", matrix[i][j]);
        if (i != M - 1) printf("\n");
    }
}

double** matrix_allocate(int M, int N) {
    double** matrix = malloc((M + M * N) * sizeof(double));
    double* start = (double*) (matrix + M);
    for (int i = 0; i < M; i++) 
        matrix[i] = start + i * N; 

    return matrix;
}

int invert(double** matrix, int M, int N) {
    int flag = 1;
    double** trans_matrix = trans(matrix, M, N);
    double** alg_comp = matrix_allocate(M-1, N-1);
    double determinant = det_recursive(matrix, M);
    if (determinant != 0) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                get_alg_comp(trans_matrix, M, i, j, alg_comp); 
                matrix[i][j] = pow(-1, i+j) * det_recursive(alg_comp, M-1) / determinant;
            }
        }
    } else flag = 0;
    free(alg_comp);
    free(trans_matrix);

    return flag;
}

double** trans(double** matrix, int M, int N) {
    double** trans_matrix = matrix_allocate(N, M);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            trans_matrix[j][i] = matrix[i][j];
    
    return trans_matrix;
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
            get_alg_comp(matrix, size, 0, j, alg_comp);
            determinant += matrix[0][j] * pow(-1, j) * det_recursive(alg_comp, size - 1);
        }
        free(alg_comp);
        break;
    }

    return determinant;
}

void get_alg_comp(double** matrix, int size, int row, int column, double** new_matrix) {
    int k = 0;
    for (int i = 0; i < size; ++i) {
        int l = 0;
        for (int j = 0; j < size; ++j) {
            if ((i != row) && (j != column)) {
                new_matrix[k][l] = matrix[i][j];
                ++l;
            }
        }
        if (i != row) ++k;
    }
}