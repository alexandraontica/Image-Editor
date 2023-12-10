#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define NR_CULORI 3
#define VAL_MIN_CULORI_TASK6 0
#define VAL_MAX_CULORI_TASK6 255

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
    if (image == NULL)
        return NULL;
    int ***img_rotita = alloc_mat(M, N);

    if (img_rotita == NULL)
        return NULL;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                img_rotita[i][j][k] = image[j][M - i - 1][k];
            }
        }
    }

    free_mat(image, N, M);

    return img_rotita;
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

    free_mat(image, N, M);

    return img_extend;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    if (x < 0 || y < 0)
        return NULL;

    // modific capetele a.i. sa nu-mi depaseasca dimensiunile matricei initiale:
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

    float ***img_cu_filtru = (float ***)malloc(N * sizeof(float **));

    for (int i = 0; i < N; i++) {
        img_cu_filtru[i] = (float **)malloc(M * sizeof(float *));

        if (img_cu_filtru[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(img_cu_filtru[j]);
            }
            free(img_cu_filtru);
            return NULL;
        }

        for (int j = 0; j < M; j++) {
            img_cu_filtru[i][j] = (float *)malloc(NR_CULORI * sizeof(float));
            if (img_cu_filtru[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(img_cu_filtru[i][k]);
                }
                for (int k = 0; k <= i; k++) {
                    free(img_cu_filtru[k]);
                }

                free(img_cu_filtru);
                return NULL;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                img_cu_filtru[i][j][k] = 0;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // verific daca pixelul are vecini inafara imaginii:
            int linii_capat_inferior = 0, coloane_capat_inferior = 0;
            int linii_capat_superior = 0, coloane_capat_superior = 0;
            int filtru_linii_capat_inferior = 0, filtru_coloane_capat_inferior = 0;
            int filtru_linii_capat_superior = 0, filtru_coloane_capat_superior = 0;

            if (i - filter_size/2 < 0) {
                linii_capat_inferior = 0;
                filtru_linii_capat_inferior = filter_size/2 - i;
            } else {
                linii_capat_inferior = i - filter_size/2;
                filtru_linii_capat_inferior = 0;
            }

            if (j - filter_size/2 < 0) {
                coloane_capat_inferior = 0;
                filtru_coloane_capat_inferior = filter_size/2 - j;
            } else {
                coloane_capat_inferior = j - filter_size/2;
                filtru_coloane_capat_inferior = 0;
            }

            if (i + filter_size/2 >= N) {
                linii_capat_superior = N-1;
                filtru_linii_capat_superior = filter_size - (i + filter_size/2 - N);
            } else {
                linii_capat_superior = i + filter_size/2;
                filtru_linii_capat_superior = filter_size;
            }

            if (j + filter_size/2 >= M) {
                coloane_capat_superior = M-1;
                filtru_coloane_capat_superior = filter_size - (j + filter_size/2 - M);
            } else {
                coloane_capat_superior = j + filter_size/2;
                filtru_coloane_capat_superior = filter_size;
            }

            for (int p = 0; p < NR_CULORI; p++) {
                for (int k = linii_capat_inferior, q = filtru_linii_capat_inferior; k <= linii_capat_superior && q < filtru_linii_capat_superior; k++, q++) {
                    for (int l = coloane_capat_inferior, t = filtru_coloane_capat_inferior; l <= coloane_capat_superior && t < filtru_coloane_capat_superior; l++, t++) {
                        img_cu_filtru[i][j][p] += (float)image[k][l][p] * filter[q][t];
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j< M; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                if (img_cu_filtru[i][j][k] < VAL_MIN_CULORI_TASK6) {
                    image[i][j][k] = VAL_MIN_CULORI_TASK6;
                } else if (img_cu_filtru[i][j][k] > VAL_MAX_CULORI_TASK6) {
                    image[i][j][k] = VAL_MAX_CULORI_TASK6;
                } else {
                    image[i][j][k] = (int)img_cu_filtru[i][j][k];
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(img_cu_filtru[i][j]);
        }
        free(img_cu_filtru[i]);
    }

    free(img_cu_filtru);

    return image;
}
