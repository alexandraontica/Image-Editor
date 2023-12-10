#include <stdio.h>
#include <stdlib.h>

#define NR_CULORI 3
#define VAL_MIN_CULORI_TASK6 0
#define VAL_MAX_CULORI_TASK6 255

int ***alloc_mat(int N, int M) {
    int ***mat = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        mat[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            mat[i][j] = (int *)malloc(NR_CULORI * sizeof(int));
        }
    }
    return mat;
}

void free_mat(int ***mat, int M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(mat[i][j]);
        }
        free(mat[i]);
    }
    free(mat);
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    if (image == NULL)
        return NULL;

    int ***img_extend = alloc_mat(N + 2 * rows, M + 2 * cols);

    for (int i = 0; i < N + 2 * rows; i++) {
        for (int j = 0; j < M + 2 * cols; j++) {
            if (i >= rows && i < rows + N && j >= cols && j < cols + M) {
                for (int k = 0; k < NR_CULORI; k++) {
                    img_extend[i][j][k] = image[i - rows][j - cols][k];
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

// float **extend_float(float **image, int N, int M, int rows, int cols) {
//     if (image == NULL)
//         return NULL;

//     float **img_cu_filtru = (float **)malloc((N + 2 * rows) * sizeof(float *));
//     for (int i = 0; i < N + 2 * rows; i++) {
//         img_cu_filtru[i] = (float *)malloc((M + 2 * cols) * sizeof(float));
//         for (int j = 0; j < M + 2 * cols; j++) {
//             if (i >= rows && i < rows + N && j >= cols && j < cols + M) {
//                 img_cu_filtru[i][j] = image[i - rows][j - cols];
//             } else {
//                 img_cu_filtru[i][j] = 0.0;
//             }
//         }
//     }

//     return img_cu_filtru;
// }



int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    if (image == NULL || x < 0 || y < 0 || x + w > M || y + h > N)
        return NULL;

    int ***img_crop = alloc_mat(h, w);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                img_crop[i][j][k] = image[y + i][x + j][k];
            }
        }
    }

    return img_crop;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    image = extend(image, N, M, filter_size / 2, filter_size / 2, 0, 0, 0);

    if (image == NULL)
        return NULL;

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
                for (int l = 0, t = i - filter_size / 2; l < filter_size && t < filter_size / 2; l++, t++) {
                    for (int p = 0, q = j - filter_size / 2; p < filter_size && q < j + filter_size / 2; p++, q++) {
                        img_cu_filtru[i][j][k] += (float)image[t][q][k] * filter[l][p];
                    }
                }
            }
        }
    }

    image = crop(image, N + filter_size, M + filter_size, filter_size / 2, filter_size / 2, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
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

int main() {
    int N = 0, M = 0;
    scanf("%d%d", &N, &M);

    int ***a = alloc_mat(N, M);

    if (a == NULL) {
        free_mat(a, N, M);
        printf("err");
        return 1;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < NR_CULORI; k++)
                scanf("%d", &a[i][j][k]);

    float matrice[3][3] = {
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0}
    };

    // Aplică filtrul și atribuie rezultatul la a
    a = apply_filter(a, N, M, (float **)matrice, 3);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < NR_CULORI; k++) {
                printf("%d ", a[i][j][k]);
            }
        }
        printf("\n");
    }

    // Eliberează memoria
    free_mat(a, N, M);

    return 0;
}
