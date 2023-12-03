#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define NR_CULORI 3

int*** alloc_mat(int M, int N) {
    int ***mat = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        mat[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            mat[i][j] = (int *)malloc(NR_CULORI * sizeof(int));
        }
    }
    return mat;
}

int*** realloc_mat(int*** mat, int M, int N, int K, int P) {
    int ***aux = (int***)realloc(mat, (M + K) * sizeof(int**));
    if (aux == NULL)
        return NULL;
    for (int i = 0; i < M + K; i++) {
        aux[i] = (int**)realloc(aux[i], (N + P) * sizeof(int*));
        if (aux[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(aux[j]);
            free(aux);
            return NULL;
        }
        for (int j = 0; j < N + P; j++) {
            aux[i][j] = (int*)realloc(aux[i][j], NR_CULORI * sizeof(int));
            if (aux[i][j] == NULL) {
                for (int k = 0; k < j; k++)
                    free(aux[i][k]);
                for (int k = 0; k < i; k++)
                    free(aux[k]);
                free(aux);
                return NULL;
            }
        }
    }
    return aux;
}

void free_mat(int ***mat, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            free(mat[i][j]);
        }
        free(mat[i]);
    }
    free(mat);
    mat = NULL;
}

// Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    if (image == NULL)
        return NULL;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            for (int k = 0; k <= NR_CULORI; k++) {
                int aux = image[i][M - j - 1][k];
                image[i][M - j - 1][k] = image[i][j][k];
                image[i][j][k] = aux;
            }
        }
    }
    return image;
}

// Task 2
int ***rotate_left(int ***image, int N, int M) {
    if (image != NULL) {
        int ***img_rotita = alloc_mat(M, N);
        if (img_rotita != NULL) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < NR_CULORI; k++) {
                        img_rotita[i][j][k] = image[N - j - 1][i][k];
                    }
                }
            }
            free_mat(image, N, M);
            return img_rotita;
        } else {
            return NULL;  // nu se poate roti imaginea pt ca nu se poate realoca la dimensiunile necesare
        }
    } else {
        return NULL;
    }
}

// Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    if (image == NULL)
        return NULL;
    return image;
}

// Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    if (image == NULL)
        return NULL;
    return image;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    return NULL;
}

// Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    if (image == NULL)
        return NULL;
    return image;
}
