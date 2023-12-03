#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int N=0, M=0;
    scanf("%d%d", &N, &M);
    int ***a=alloc_mat(N,M);
    if(a==NULL) { 
        free_mat(a,N,M);
        printf("err");
        return 0;
    }
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            for(int k=0;k<NR_CULORI;k++)
                scanf("%d", &a[i][j][k]);
    a=rotate_left(a, N, M);
    int aux = N;
    N = M;
    M = aux;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            for(int k=0;k<NR_CULORI;k++)
                printf("%d", a[i][j][k]);
    return 0;
}