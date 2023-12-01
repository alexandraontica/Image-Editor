#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define NO_MAX_OF_COLOR 8388607

// Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            for (int k = 0; k <= NO_MAX_OF_COLOR; k++) {
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
    return image;
}

// Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    return NULL;
}

// Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    return NULL;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    return NULL;
}

// Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    return NULL;
}
