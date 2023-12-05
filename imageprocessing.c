#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define NR_CULORI 3

int*** alloc_mat(int M, int N) {
    int ***mat = (int ***)malloc(M * sizeof(int **));

    for (int i = 0; i < M; i++) {
        mat[i] = (int **)malloc(N * sizeof(int *));

        if (mat[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }

        for (int j = 0; j < N; j++) {
            mat[i][j] = (int *)malloc(NR_CULORI * sizeof(int));
            if (mat[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(mat[i][k]);
                }
                for (int k = 0; k <= i; k++) {
                    free(mat[k]);
                }

                free(mat);
                return NULL;
            }
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
    if (image == NULL)  // nu a reusit alocarea dinamica pt imaginea initiala
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
                        img_rotita[i][j][k] = image[j][M - i - 1][k];
                    }
                }
            }

            free_mat(image, N, M);

            return img_rotita;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

// Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    if (image == NULL || x < 0 || y < 0 || x + w > M || y + h > N)
        return NULL;

    int ***img_crop = alloc_mat(h, w);

    if (img_crop == NULL) {
        return NULL;
    }

    int p = 0, l = 0;

    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                img_crop[p][l][k] = image[i][j][k];
            }
            l++;
        }
        p++;
        l = 0;
    }

    free_mat(image, N, M);

    return img_crop;
}

// Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    if (image == NULL)
        return NULL;

    int ***img_extend = alloc_mat(N + 2 * rows, M + 2 * cols);

    if (img_extend == NULL)
        return NULL;

    int p = 0, l = 0;
    for (int i = 0; i < N + 2 * rows; i++) {
        for (int j = 0; j < M + 2 * cols; j++) {
            if (i >= rows && i < rows + N && j >= cols && j < cols + M) {
                for (int k = 0; k < NR_CULORI; k++) {
                    img_extend[i][j][k] = image[p][l][k];
                }

                if (l == M - 1) {
                    p++;
                    l = 0;
                } else {
                    l++;
                }
            } else {
                img_extend[i][j][0] = new_R;
                img_extend[i][j][1] = new_G;
                img_extend[i][j][2] = new_B;
            }
        }
    }

    return img_extend;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    if (x < 0 || y < 0)
        return NULL;

    if (N_dst < y + N_src) {
        N_src = N_dst - y;
    }

    if (M_dst < x + M_src) {
        M_src = M_dst - x;
    }

    int p = 0, l = 0;
    for (int i = 0; i < N_dst; i++) {
        for (int j = 0; j < M_dst; j++) {
            if (i >= y && i < y + N_src && j >= x && j < x + M_src) {
                for (int k = 0; k < NR_CULORI; k++) {
                    image_dst[i][j][k] = image_src[p][l][k];
                }

                if (l == M_src - 1) {
                    p++;
                    l = 0;
                } else {
                    l++;
                }
            }
        }
    }
    return image_dst;
}

// Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    if (image == NULL)
        return NULL;

    if (filter == NULL)
        return image;

    return image;
}
