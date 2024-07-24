#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#define NUM_COLORS 3
#define VAL_MIN_COLORS 0
#define VAL_MAX_COLORS 255

int ***alloc_mat(int M, int N);
void free_mat(int ****mat, int M, int N);
int ***flip_horizontal(int ***image, int N, int M);
int ***flip_vertical(int ***image, int N, int M);
int ***rotate_left(int ***image, int N, int M);
int ***rotate_right(int ***image, int N, int M);
int ***crop(int ***image, int N, int M, int x, int y, int h, int w);
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B);
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y);
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size);
void print_commands();

#endif  // IMAGEPROCESSING_H
